// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeLobby.h"
#include "GameStateLobby.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "Player/WraithState.h"

AGameModeLobby::AGameModeLobby()
{
	bUseSeamlessTravel = true;
}

FString AGameModeLobby::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
												 const FString& Options, const FString& Portal)
{
	FString Result = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

	if (AWraithState* PlayerState = Cast<AWraithState>(NewPlayerController->PlayerState))
	{
		// Extract parameters from the connection options ("SkinIndex")
		FString SkinIndexOption;
		if (FParse::Value(*Options, TEXT("SkinIndex="), SkinIndexOption))
		{
			const int ParsedSkinIndex = FCString::Atoi(*SkinIndexOption);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Skin Index Option : %d"), ParsedSkinIndex));
			PlayerState->SkinIndex = ParsedSkinIndex;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("InitNewPlayer called"));

	return Result;
}

void AGameModeLobby::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Post Login"));

	if (GameState->PlayerArray.Num() >= 2 && !isTimerStarted)
	{ 
		// Start timer after 3 seconds so it give the time to the PC to initialize
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGameModeLobby::StartCountdown, 3.f, false);
		isTimerStarted = true;
	}
}

void AGameModeLobby::StartCountdown() const
{
	if (AGameStateLobby* CurrentGameState = GetGameState<AGameStateLobby>())
	{
		CurrentGameState->TimerEnd = GetWorld()->TimeSeconds + 10;
		CurrentGameState->OnRep_TimerEnd();
	}
}

void AGameModeLobby::StartGame() const
{
	if (const auto World = GetWorld())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ServerTravel"));
		World->ServerTravel("/Game/Game/Levels/Main");
	}
}