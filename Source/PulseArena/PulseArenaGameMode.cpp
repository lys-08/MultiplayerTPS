// Copyright Epic Games, Inc. All Rights Reserved.

#include "PulseArenaGameMode.h"
#include "PulseArenaCharacter.h"
#include "UObject/ConstructorHelpers.h"

APulseArenaGameMode::APulseArenaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
