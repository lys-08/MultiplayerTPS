// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameStateLobby.generated.h"

/**
 * Lobby Game State
 */
UCLASS()
class PULSEARENA_API AGameStateLobby : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, ReplicatedUsing=OnRep_TimerEnd, Category = "Timer") float TimerEnd;

	// Delegate
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerEndChangedSignature, float, TimerEnd);
	UPROPERTY() FOnTimerEndChangedSignature OnTimerEndChanged;

	UFUNCTION() void OnRep_TimerEnd() const;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
