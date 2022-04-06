#pragma once

namespace Offsets
{
	//If there is an offset that is being used for core gameplay put it here if not just find it
	//where the function is.
	//TODO: Move all of the offsets here
	DWORD InventoryOffset;
	DWORD ItemGuidOffset;
	DWORD ItemDefinitionOffset;
	DWORD PrimQuickBarOffset;
	DWORD EntriesOffset;
	DWORD PickupEntryOffset;
	DWORD EntryCountOffset;
	DWORD LastEmotePlayedOffset;

	static void InitPreDefinedOffsets()
	{
		InventoryOffset = FindOffset("FortInventory", "Inventory");
		EntriesOffset = FindOffset("FortItemList", "ReplicatedEntries");
		ItemGuidOffset = FindOffset("FortItemEntry", "ItemGuid");
		ItemDefinitionOffset = FindOffset("FortItemEntry", "ItemDefinition");
		PrimQuickBarOffset = FindOffset("FortQuickBars", "PrimaryQuickBar");
		PickupEntryOffset = FindOffset("FortPickup", "PrimaryPickupItemEntry");
		EntryCountOffset = FindOffset("FortItemEntry", "Count");
		LastEmotePlayedOffset = FindOffset("FortPlayerController", "LastEmotePlayed");
	}
}

namespace Patterns
{
	const char* GetEngineVersion = crypt("40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 8B C8 41 B8 ? ? ? ? 48 8B D3 E8 ? ? ? ? 48 8B C3");

	namespace C2
	{
		const char* World = crypt("48 8B 05 ? ? ? ? 4D 8B C2"); //true, 3
		const char* GObjects = crypt("48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1"); //true, 3
		const char* FreeMemory = crypt("48 85 C9 0F 84 ? ? ? ? 53 48 83 EC 20 48 89 7C 24 30 48 8B D9 48 8B 3D ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 48 8B 07 4C 8B 40 30 48 8D 05 ? ? ? ? 4C 3B C0");
		const char* FNameToString = crypt("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 33 F6 48 8B F2 44 39 71 04 0F 85 ? ? ? ? 8B 19 0F B7 FB E8 ? ? ? ? 8B CB 48 8D 54 24");
		const char* Notification = crypt("4C 8B DC 55 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 89 73 F0 49 89 7B E8 48 8B F9 4D 89 63 E0 4D 8B E0 4D 89 6B D8");
		const char* FNCrash = crypt("");
		const char* SpawnActor = crypt("48 8b c4 55 53 56 57 41 54 41 55 41 56 41 57 48 8d a8 ? ? ? ? 48 81 ec ? ? ? ? 0f 29 70 ? 0f 29 78 ? 44 0f 29 40 ? 44 0f 29 88 ? ? ? ? 44 0f 29 90 ? ? ? ? 44 0f 29 98 ? ? ? ? 44 0f 29 a0 ? ? ? ? 44 0f 29 a8 ? ? ? ? 44 0f 29 b0 ? ? ? ? 44 0f 29 b8 ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 45 ? 45 33 ed");
		const char* RequestExitWithStatus = crypt("48 89 5C 24 ? 57 48 83 EC 40 41 B9 ? ? ? ? 0F B6 F9 44 38 0D ? ? ? ? 0F B6 DA 72 24 89 5C 24 30 48 8D 05 ? ? ? ? 89 7C 24 28 4C 8D 05 ? ? ? ? 33 D2 48 89 44 24 ? 33 C9 E8 ? ? ? ?");
	}

	namespace C3
	{
		const char* World = crypt("48 8B 05 ? ? ? ? 4D 8B C1"); //true, 3
		const char* GObjects = crypt("48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1"); //true, 3
		const char* FNameToString = crypt("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B F2 4C 8B F1 E8 ? ? ? ? 45 8B 06 33 ED");
		const char* FreeMemory = crypt("48 85 C9 0F 84 ? ? ? ? 53 48 83 EC 20 48 89 7C 24 30 48 8B D9 48 8B 3D ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 48 8B 07 4C 8B 40 30 48 8D 05 ? ? ? ? 4C 3B C0");
		const char* Notification = crypt("4C 8B DC 55 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 89 5B 20");
		const char* FNCrash = crypt("48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 60 20 55 41 56 41 57 48 8B EC 48 83 EC 40 45 33 FF 4C 8D 35 ? ? ? ?");
		const char* SpawnActor = crypt("48 8b c4 55 53 56 57 41 54 41 55 41 56 41 57 48 8d a8 ? ? ? ? 48 81 ec ? ? ? ? 0f 29 70 ? 0f 29 78 ? 44 0f 29 40 ? 44 0f 29 88 ? ? ? ? 44 0f 29 90 ? ? ? ? 44 0f 29 98 ? ? ? ? 44 0f 29 a0 ? ? ? ? 44 0f 29 a8 ? ? ? ? 44 0f 29 b0 ? ? ? ? 44 0f 29 b8 ? ? ? ? 48 8b 05 ? ? ? ? 48 33 c4 48 89 45 ? 45 33 ed");
		const char* RequestExitWithStatus = crypt("48 8B C4 48 89 58 18 88 50 10 88 48 08 57 48 83 EC 30");
	}
}