// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItem.h"
#include "InventoryComponent.generated.h"



//class AItem;

//Delegate to bind BP to update Inventory
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_ROOM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	UFUNCTION(BlueprintCallable)
	bool AddItem(FItemDetailStruct ItemStruct);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(FItemDetailStruct ItemStruct);

	UFUNCTION(BlueprintCallable)
	bool CompareToUsedItem(FItemDetailStruct ItemStruct);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FItemDetailStruct> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SlotsAmount = 8;

	UPROPERTY(BlueprintReadWrite)
	FItemDetailStruct CurrentlyUsedItem;
};
