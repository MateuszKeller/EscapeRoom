// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Interactable.h"
#include "InspectionItem.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class ESCAPE_ROOM_API AInspectionItem : public AItem, public IInteractable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInspectionItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	///IInteractable:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnLookAt(APlayerCharacter* Player);
	virtual void OnLookAt_Implementation(APlayerCharacter* Player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(APlayerCharacter* Player);
	virtual void OnInteract_Implementation(APlayerCharacter* Player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnStopLooking();
	virtual void OnStopLooking_Implementation();

	void DropItem();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName ItemName = FName(*FString("Default Item"));;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText Message = FText::FromString("[E] Inspect");;

	UPROPERTY(VisibleInstanceOnly, Category = "Item")
	FTransform ItemWorldPosition;

	UPROPERTY(VisibleInstanceOnly, Category = "Item")
	FVector GripPointPosition;	
};
