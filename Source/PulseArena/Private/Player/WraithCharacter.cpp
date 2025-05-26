// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WraithCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Player/WraithController.h"
#include "Player/WraithState.h"
#include "UI/TimerWidget.h"

void AWraithCharacter::OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
	Super::OnPlayerStateChanged(NewPlayerState, OldPlayerState);

	if(AWraithState* PS = Cast<AWraithState>(NewPlayerState))
	{
		PS->OnSkinIndexChanged.AddDynamic(this, &AWraithCharacter::ApplySkin);
		ApplySkin();
	}
}

void AWraithCharacter::Server_ChangeSkinIndex_Implementation(int SkinIndex)
{
	if(AWraithState* PS = Cast<AWraithState>(GetPlayerState()))
	{
		PS->SetSkinIndex(SkinIndex);
	}
}

void AWraithCharacter::ApplySkin()
{
	const int SkinIndex = Cast<AWraithState>(GetPlayerState())->SkinIndex;

	if (SkinMap.Contains(SkinIndex))
	{
		GetMesh()->SetMaterial(0, SkinMap[SkinIndex]);
	}
}

void AWraithCharacter::CreateTimerWidget(float timerEnd)
{
	float timerTime = timerEnd;

	if (HasAuthority())
	{
		timerTime -= GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (AWraithController* PC = Cast<AWraithController>(GetWorld()->GetFirstPlayerController()))
		{
			float serverDelta = PC->GetServerWorldTimeDelta();
			
			if (serverDelta <= 0.0f)
			{
				FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AWraithCharacter::CreateTimerWidget, timerEnd);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.1f, false);
				return;
			}

			GetWorldTimerManager().ClearTimer(TimerHandle);
			float serverTime = PC->GetServerWorldTime();
			timerTime -= serverTime;
		}
	}
	
	if (UTimerWidget* CountdownWidget = CreateWidget<UTimerWidget>(GetWorld(), CountdownWidgetClass))
	{
		CountdownWidget->AddToViewport();
		CountdownWidget->SetTime(timerTime);
	}
}