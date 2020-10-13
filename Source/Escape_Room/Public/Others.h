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