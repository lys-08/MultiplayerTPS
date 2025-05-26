// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WraithState.generated.h"

/**
 * Player State that manage the skin index of the player
 */
UCLASS()
class PULSEARENA_API AWraithState : public APlayerState
{
	GENERATED_BODY()

public:
	// Delegate
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkinIndexChangeSignature);
	UPROPERTY() FOnSkinIndexChangeSignature OnSkinIndexChanged;
	
	AWraithState();
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_SkinIndex, Category = "Customization") int SkinIndex;
	UFUNCTION(BlueprintCallable, Category = "Customization") void SetSkinIndex(int NewSkinIndex);
	UFUNCTION() void OnRep_SkinIndex() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// For Persistency
	virtual void CopyProperties(APlayerState* PlayerState) override;
};
