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
	FName ItemName = FName(*FString("Default Item"));

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMesh* ItemMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UTexture2D* ItemThumbnail = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TSubclassOf<AInventoryItem> ItemClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText Message = FText::FromString("[E] Take");

	bool operator==(const FItemDetailStruct& other) const {
		return ItemName == other.ItemName && ItemClass == other.ItemClass;
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

	void DropItem();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FItemDetailStruct ItemDetails;
};
