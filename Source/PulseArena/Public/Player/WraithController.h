// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WraithController.generated.h"

/**
 * Player Character Controller
 * -> manage the network clock synchronization (inspired by Alvaro Jover-Alvarez : https://vorixo.github.io/devtricks/non-destructive-synced-net-clock/)
 */
UCLASS()
class PULSEARENA_API AWraithController : public APlayerController
{
	GENERATED_BODY()
	
#pragma region NetworkClockSync

protected:
	// Frequency that the client requests to adjust it's local clock. Set to zero to disable periodic updates
	UPROPERTY(EditDefaultsOnly, Category=GameState) float NetworkClockUpdateFrequency = 5.f;

private:
	float ServerWorldTimeDelta = 0.f; // STT : ServerTimeTrip
	TArray<float> RTTCircularBuffer; // Buffer of RoundTripTime : Round Time Trip

	public:
	UFUNCTION(BlueprintPure) float GetServerWorldTimeDelta() const;
	UFUNCTION(BlueprintPure) float GetServerWorldTime() const;

	virtual void BeginPlay() override;
	virtual void PostNetInit() override;

private:
	void RequestWorldTime_Internal();
	UFUNCTION(Server, Unreliable) void Server_RequestWorldTime(float ClientTimestamp);
	UFUNCTION(Client, Unreliable) void Client_UpdateWorldTime(float ClientTimestamp, float ServerTimestamp);

#pragma endregion NetworkClockSync
};
