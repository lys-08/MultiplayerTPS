// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeLobby.generated.h"

/**
 * Game mode class for the multiplayer lobby's room
 */
UCLASS()
class PULSEARENA_API AGameModeLobby : public AGameMode
{
	GENERATED_BODY()
	
	bool isTimerStarted = false;
    	
    AGameModeLobby();
    virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
    	const FString& Options, const FString& Portal) override;
    virtual void PostLogin(APlayerController* NewPlayer) override;
    void StartCountdown() const;

public:
    void StartGame() const;
};
