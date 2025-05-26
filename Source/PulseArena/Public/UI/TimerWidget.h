// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class PULSEARENA_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

	float time;
	FTimerHandle TimerHandle;

public:
	UPROPERTY(meta = (BindWidget)) UTextBlock* TimeText;
	
	void SetTime(float startTime);
	UFUNCTION(BlueprintCallable) void UpdateTime();

private:
	void ConvertTime() const;
};
