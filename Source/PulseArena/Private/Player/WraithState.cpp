// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WraithState.h"

#include "Net/UnrealNetwork.h"
#include "Player/WraithCharacter.h"

AWraithState::AWraithState()
{
	bReplicates = true; // enable replication
	SkinIndex = 0;
}

void AWraithState::SetSkinIndex(int NewSkinIndex)
{
	AWraithCharacter* PlayerCharacter = Cast<AWraithCharacter>(GetOwningController()->GetPawn());
	
	if (HasAuthority())
	{
		SkinIndex = NewSkinIndex;
		PlayerCharacter->ApplySkin();
	}
	else 
	{
		PlayerCharacter->Server_ChangeSkinIndex(NewSkinIndex);
	}
}

void AWraithState::OnRep_SkinIndex() const
{
	OnSkinIndexChanged.Broadcast();
}

void AWraithState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWraithState, SkinIndex);
}

void AWraithState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (AWraithState* NewPlayerState = Cast<AWraithState>(PlayerState))
	{
		NewPlayerState->SkinIndex = SkinIndex;
	}
}