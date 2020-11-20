// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "PuzzlePartItem.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class ESCAPE_ROOM_API APuzzlePartItem : public AInventoryItem
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APuzzlePartItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnClickedTake(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION()
	void OnStartHover(AActor* TouchedActor);

	UFUNCTION()
	void OnEndHover(AActor* TouchedActor);

};
