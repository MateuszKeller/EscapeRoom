// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "InventoryItem.generated.h"


USTRUCT(BlueprintType)
struct FItemDetailStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemName = FText::FromString("Default Item");

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item")
	UStaticMesh* ItemMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UTexture2D* ItemThumbnail = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AInventoryItem> ItemClass = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item")
	FTransform ItemTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText Message = FText::FromString("[E] Take");

	bool operator==(const FItemDetailStruct& other) const {
		return ItemName.EqualTo(other.ItemName) && ItemClass == other.ItemClass;
	}

};

/**
 * 
 */
UCLASS(ABSTRACT)
class ESCAPE_ROOM_API AInventoryItem : public AItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventoryItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void Take(APlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	void InspectFromInventory();

	void DropItem();

	UFUNCTION(BlueprintCallable)
	bool IsNotWalking();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItemDetailStruct ItemDetails;
	
	UPROPERTY(BlueprintReadWrite, Category = "Item")
	bool bInsideInventory = false;
};
