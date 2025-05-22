// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerGameInstanceSubsystem.generated.h"

/**
 * Multiplayer Subsystem to be in charge of hosting and joining a game
 */
UCLASS()
class PULSEARENA_API UMultiplayerGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "1"), Category = "Game")
	void HostGame(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld> Level,
		bool bAbsolute, FString Options);
		
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "1"), Category = "Game")
	void JoinGame(const UObject* WorldContextObject, FString IpAdress); 
};
