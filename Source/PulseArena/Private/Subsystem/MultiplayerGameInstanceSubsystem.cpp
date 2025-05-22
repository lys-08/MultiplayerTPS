// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/MultiplayerGameInstanceSubsystem.h"

#include "Player/WraithState.h"

void UMultiplayerGameInstanceSubsystem::HostGame(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld> Level,
                                                 bool bAbsolute, FString Options)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World == nullptr)
	{
		return;
	}

	const ETravelType TravelType = (bAbsolute ? TRAVEL_Absolute : TRAVEL_Relative);
	FWorldContext &WorldContext = GEngine->GetWorldContextFromWorldChecked(World);
	const FName LevelName = FName(*FPackageName::ObjectPathToPackageName(Level.ToString()));
	FString Cmd = LevelName.ToString();
	if (Options.Len() > 0)
	{
		Cmd += FString(TEXT("?")) + Options;
	}
	FURL TestURL(&WorldContext.LastURL, *Cmd, TravelType);
	if (TestURL.IsLocalInternal())
	{
		// make sure the file exists if we are opening a local file
		if (!GEngine->MakeSureMapNameIsValid(TestURL.Map))
		{
			UE_LOG(LogLevel, Warning, TEXT("WARNING: The map '%s' does not exist."), *TestURL.Map);
		}
	}

	GEngine->SetClientTravel(World, *Cmd, TravelType );
}

void UMultiplayerGameInstanceSubsystem::JoinGame(const UObject* WorldContextObject, FString IpAddress)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World == nullptr)
	{
		return;
	}
    
	GEngine->SetClientTravel(World, *IpAddress, ETravelType::TRAVEL_Absolute);
}