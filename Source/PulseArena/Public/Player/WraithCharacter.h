// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PulseArenaCharacter.h"
#include "WraithCharacter.generated.h"

/**
 * Player Character class
 */
UCLASS()
class PULSEARENA_API AWraithCharacter : public APulseArenaCharacter
{
	GENERATED_BODY()

	FTimerHandle TimerHandle;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<class UTimerWidget> CountdownWidgetClass;
	UPROPERTY(EditAnywhere, Category = "Customization") TMap<int, UMaterial*> SkinMap; // materials map

	virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;
	
	UFUNCTION(Server, Reliable) void Server_ChangeSkinIndex(int SkinIndex);
	UFUNCTION() void ApplySkin();
	UFUNCTION() void CreateTimerWidget(float startingTime);
};
