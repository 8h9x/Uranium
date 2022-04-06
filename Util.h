#pragma once

#include <consoleapi.h>
#include <cstdio>
#include <vector>
#include <libloaderapi.h>
#include <Psapi.h>
#include <string>

#define ShowMessage(message) MessageBoxA(NULL, message, crypt("Uranium"), MB_OK)
#define CHECKSIG(sig, error) if (!sig) { ShowMessage(error); }

#define DetoursEasy(address, hook) \
	DetourTransactionBegin(); \
    DetourUpdateThread(GetCurrentThread()); \
    DetourAttach(&(PVOID&)address, hook); \
    DetourTransactionCommit();

enum ASM : DWORD
{
	JMP_REL8 = 0xEB,
	CALL = 0xE8,
	LEA = 0x8D,
	CDQ = 0x99,
	CMOVL = 0x4C,
	CMOVS = 0x48,
	INT3 = 0xCC,
	RETN = 0xC3,
	SKIP
};

class Util
{
public:
	static void InitConsole()
	{
		AllocConsole();

		FILE* pFile;
		freopen_s(&pFile, "CONOUT$", "w", stdout);
	}

	static __forceinline uintptr_t FindPattern(const char* signature, bool bRelative = false, uint32_t offset = 0)
	{
		uintptr_t base_address = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
		static auto patternToByte = [](const char* pattern)
		{
			auto bytes = std::vector<int>{};
			const auto start = const_cast<char*>(pattern);
			const auto end = const_cast<char*>(pattern) + strlen(pattern);

			for (auto current = start; current < end; ++current)
			{
				if (*current == '?')
				{
					++current;
					if (*current == '?') ++current;
					bytes.push_back(-1);
				}
				else { bytes.push_back(strtoul(current, &current, 16)); }
			}
			return bytes;
		};

		const auto dosHeader = (PIMAGE_DOS_HEADER)base_address;
		const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)base_address + dosHeader->e_lfanew);

		const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto patternBytes = patternToByte(signature);
		const auto scanBytes = reinterpret_cast<std::uint8_t*>(base_address);

		const auto s = patternBytes.size();
		const auto d = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - s; ++i)
		{
			bool found = true;
			for (auto j = 0ul; j < s; ++j)
			{
				if (scanBytes[i + j] != d[j] && d[j] != -1)
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				uintptr_t address = reinterpret_cast<uintptr_t>(&scanBytes[i]);
				if (bRelative)
				{
					address = ((address + offset + 4) + *(int32_t*)(address + offset));
					return address;
				}
				return address;
			}
		}
		return NULL;
	}

	static inline BOOL MaskCompare(PVOID pBuffer, LPCSTR lpPattern, LPCSTR lpMask)
	{
		for (auto value = reinterpret_cast<PBYTE>(pBuffer); *lpMask; ++lpPattern, ++lpMask, ++value)
		{
			if (*lpMask == 'x' && *reinterpret_cast<LPCBYTE>(lpPattern) != *value)
				return false;
		}

		return true;
	}

	static inline PVOID FindPattern(PVOID pBase, DWORD dwSize, LPCSTR lpPattern, LPCSTR lpMask)
	{
		dwSize -= static_cast<DWORD>(strlen(lpMask));

		for (auto index = 0UL; index < dwSize; ++index)
		{
			auto pAddress = reinterpret_cast<PBYTE>(pBase) + index;

			if (MaskCompare(pAddress, lpPattern, lpMask))
				return pAddress;
		}

		return NULL;
	}

	static inline PVOID FindPattern(LPCSTR lpPattern, LPCSTR lpMask)
	{
		MODULEINFO info = { 0 };

		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info));

		return FindPattern(info.lpBaseOfDll, info.SizeOfImage, lpPattern, lpMask);
	}

	static void* FindStringRef(const std::wstring& string)
	{
		uintptr_t base_address = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

		const auto dosHeader = (PIMAGE_DOS_HEADER)base_address;
		const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)base_address + dosHeader->e_lfanew);

		IMAGE_SECTION_HEADER* textSection = nullptr;
		IMAGE_SECTION_HEADER* rdataSection = nullptr;

		auto sectionsSize = ntHeaders->FileHeader.NumberOfSections;
		auto section = IMAGE_FIRST_SECTION(ntHeaders);

		for (WORD i = 0; i < sectionsSize; section++)
		{
			auto secName = std::string((char*)section->Name);

			if (secName == ".text")
			{
				textSection = section;
			}
			else if (secName == ".rdata")
			{
				rdataSection = section;
			}

			if (textSection && rdataSection)
				break;
		}

		auto textStart = base_address + textSection->VirtualAddress;

		auto rdataStart = base_address + rdataSection->VirtualAddress;
		auto rdataEnd = rdataStart + rdataSection->Misc.VirtualSize;

		const auto scanBytes = reinterpret_cast<std::uint8_t*>(textStart);

		//scan only text section
		for (DWORD i = 0x0; i < textSection->Misc.VirtualSize; i++)
		{
			if (&scanBytes[i])
			{
				if ((scanBytes[i] == ASM::CMOVL || scanBytes[i] == ASM::CMOVS) && scanBytes[i + 1] == ASM::LEA)
				{
					auto stringAdd = reinterpret_cast<uintptr_t>(&scanBytes[i]);
					stringAdd = stringAdd + 7 + *reinterpret_cast<int32_t*>(stringAdd + 3);

					//check if the pointer is actually a valid string by checking if it's inside the rdata section
					if (stringAdd > rdataStart && stringAdd < rdataEnd)
					{
						std::wstring lea((wchar_t*)stringAdd);

						if (lea == string)
						{
							return &scanBytes[i];
						}
					}
				}
			}
		}

		return nullptr;
	}

	static void* FindByString(const std::wstring& string, std::vector<int> opcodesToFind = {}, bool bRelative = false, uint32_t offset = 0, bool forward = false)
	{
		auto ref = FindStringRef(string);

		if (ref)
		{
			printf("Ref %ls %p\n", string.c_str(), ref);


			const auto scanBytes = static_cast<std::uint8_t*>(ref);

			//scan backwards till we hit a ret (and assume this is the function start)
			for (auto i = 0; forward ? (i < 2048) : (i > -2048); forward ? i++ : i--)
			{
				if (opcodesToFind.size() == 0)
				{
					if (scanBytes[i] == ASM::INT3 || scanBytes[i] == ASM::RETN)
					{
						return &scanBytes[i + 1];
					}
				}
				else
				{
					for (uint8_t byte : opcodesToFind)
					{
						if (scanBytes[i] == byte && byte != ASM::SKIP)
						{
							if (bRelative)
							{
								uintptr_t address = reinterpret_cast<uintptr_t>(&scanBytes[i]);
								address = ((address + offset + 4) + *(int32_t*)(address + offset));
								return (void*)address;
							}
							return &scanBytes[i];
						}
					}
				}
			}
		}

		return nullptr;
	}
};