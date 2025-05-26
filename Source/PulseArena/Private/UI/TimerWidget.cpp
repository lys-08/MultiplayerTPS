// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TimerWidget.h"
#include "GameModeLobby.h"
#include "Engine/Engine.h"

void UTimerWidget::SetTime(float startTime)
{
	time = startTime;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTimerWidget::UpdateTime, 0.1f, true);
}

void UTimerWidget::UpdateTime()
{
	time -= 0.1f;

	if (time <= 0.00f)
	{
		time = 0.0f;
		if (AGameModeLobby* GM = Cast<AGameModeLobby>(GetWorld()->GetAuthGameMode()))
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			GM->StartGame();
		}
	}
	ConvertTime();
}

void UTimerWidget::ConvertTime() const
{
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%2.2f"), time)));
	}
}