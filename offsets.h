#pragma once
#include <Windows.h>
#include "UE5.h"

namespace Offsets
{
	UObject* SwitchLevelFunc;

	DWORD CheatManagerOffset = 0;
	DWORD AbilitySystemComponentOffset = 0;
	DWORD GrantedAbilitiesOffset = 0;
	DWORD DurationPolicyOffset = 0;
	DWORD CurrentPlaylistInfoOffset = 0;
	DWORD BasePlaylistOffset = 0;
	DWORD OwningGameInstanceOffset = 0;
	DWORD LocalPlayersOffset = 0;
	DWORD PlayerControllerOffset = 0;
	DWORD AcknowledgedPawnOffset = 0;
	DWORD PlayerStateOffset = 0;
	DWORD GameInstanceOffset = 0;
	DWORD InfiniteAmmoOffset = 0;
	DWORD CosmeticLoadoutPCOffset = 0;
	DWORD WeaponDefinitionOffset = 0;
	DWORD MeshOffset = 0;

	static void InitOffsets()
	{
		CheatManagerOffset = FindOffset("PlayerController", "CheatManager");
		AbilitySystemComponentOffset = FindOffset("FortPawn", "AbilitySystemComponent");
		GrantedAbilitiesOffset = FindOffset("GameplayEffect", "GrantedAbilities");
		DurationPolicyOffset = FindOffset("GameplayEffect", "DurationPolicy");
		CurrentPlaylistInfoOffset = FindOffset("FortGameStateAthena", "CurrentPlaylistInfo");
		BasePlaylistOffset = FindOffset("PlaylistPropertyArray", "BasePlaylist");
		OwningGameInstanceOffset = FindOffset("World", "OwningGameInstance");
		LocalPlayersOffset = FindOffset("GameInstance", "LocalPlayers");
		PlayerControllerOffset = FindOffset("Player", "PlayerController");
		AcknowledgedPawnOffset = FindOffset("PlayerController", "AcknowledgedPawn");
		PlayerStateOffset = FindOffset("Pawn", "PlayerState");
		GameInstanceOffset = FindOffset("GameEngine", "GameInstance");
		InfiniteAmmoOffset = FindOffset("FortPlayerController", "bInfiniteAmmo");
		CosmeticLoadoutPCOffset = FindOffset("FortPlayerController", "CosmeticLoadoutPC");
		WeaponDefinitionOffset = FindOffset("AthenaPickaxeItemDefinition", "WeaponDefinition");
		MeshOffset = FindOffset("Character", "Mesh");

	}

	static void InitFuncs()
	{
	}
}