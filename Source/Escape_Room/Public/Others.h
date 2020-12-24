// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerCharacterState : uint8
{
	None		UMETA(DisplayName = "Player"),
	Inspection	UMETA(DisplayName = "Inspection"),
	Puzzle		UMETA(DisplayName = "Puzzle")
};


/*###
DrawDebugLine(GetWorld(), CameraLocation, End, FColor::Orange, false, 2.0f);
GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("*.cpp - %s"), *));
*/
