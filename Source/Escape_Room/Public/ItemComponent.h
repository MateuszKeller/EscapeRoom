// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItem.h"
#include "ItemComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_ROOM_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool CheckUsedItem();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TArray<TSubclassOf<AInventoryItem>> KeyItemClasses;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TSubclassOf<AInventoryItem> ItemClass = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	UStaticMesh* DummyMesh = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	FVector Scale;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	FText ItemName;
};
