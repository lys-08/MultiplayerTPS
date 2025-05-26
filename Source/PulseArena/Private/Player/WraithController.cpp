// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WraithController.h"

#include "GameStateLobby.h"
#include "Player/WraithCharacter.h"

float AWraithController::GetServerWorldTimeDelta() const
{
	return ServerWorldTimeDelta;
}

float AWraithController::GetServerWorldTime() const
{
	return GetWorld()->GetTimeSeconds() + ServerWorldTimeDelta;
}

void AWraithController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AWraithCharacter* PlayerCharacter = Cast<AWraithCharacter>(GetPawn()))
	{
		if (AGameStateLobby* GS = Cast<AGameStateLobby>(GetWorld()->GetGameState()))
		{
			GS->OnTimerEndChanged.AddDynamic(PlayerCharacter, &AWraithCharacter::CreateTimerWidget);
		}
	}
}

void AWraithController::PostNetInit()
{
	Super::PostNetInit();

	// If we don't have the authority (the server doesn't need his own time), we set a timer to determine the server time (to calculate the delta)
	if (GetLocalRole() != ROLE_Authority)
	{
		RequestWorldTime_Internal();
		if (NetworkClockUpdateFrequency > 0.f)
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::RequestWorldTime_Internal, NetworkClockUpdateFrequency, true);
		}
	}
}

/**
 * Function called each 0.1s
 */
void AWraithController::RequestWorldTime_Internal()
{
	Server_RequestWorldTime(GetWorld()->GetTimeSeconds()); // Start RPC
}

/**
 * The client asked the server it's time
 * 
 * @param ClientTimestamp Client time (when the message is send)
 */
void AWraithController::Server_RequestWorldTime_Implementation(float ClientTimestamp)
{
	const float Timestamp = GetWorld()->GetTimeSeconds();
	Client_UpdateWorldTime(ClientTimestamp, Timestamp);
}

/**
 * Methods send to the clients when the server time has been asked
 * 
 * @param ClientTimestamp Client time (when the message has been send)
 * @param ServerTimestamp Server time (it's time when the message has been received)
 */
void AWraithController::Client_UpdateWorldTime_Implementation(float ClientTimestamp, float ServerTimestamp)
{
	const float CurrRTT = GetWorld()->GetTimeSeconds() - ClientTimestamp; // Round Trip Time : CurrentTime - OldTimeStamp
	RTTCircularBuffer.Add(CurrRTT);
	float adjustedRTT = 0.;

	if (RTTCircularBuffer.Num() == 10)
	{
		TArray<float> tmp = RTTCircularBuffer;
		tmp.Sort();
		for (int i = 1; i < 9; i++)
		{
			adjustedRTT += tmp[i];
		}
		adjustedRTT /= 8.0;
		RTTCircularBuffer.RemoveAt(0);
	}
	else
	{
		adjustedRTT = CurrRTT;
	}
	
	const float STT = adjustedRTT / 2.0; // Server Trip Time : RTT / 2
	const float currentServerTime = ServerTimestamp + adjustedRTT / 2.0; // current server time
	ServerWorldTimeDelta = currentServerTime - GetWorld()->GetTimeSeconds();
}