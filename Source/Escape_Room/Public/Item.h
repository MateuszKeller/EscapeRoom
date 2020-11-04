// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Engine/StaticMesh.h"
#include "Item.generated.h"

class APlayerCharacter;

USTRUCT(BlueprintType)
struct FItemDetailStruct
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item")
	FString ItemName = "Default Item";

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	UStaticMesh* ItemMesh = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item")
	UTexture2D* ItemThumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TSubclassOf<AItem> ItemClass = nullptr;
};

UCLASS()
class ESCAPE_ROOM_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	///IInteractable:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void OnLookAt(APlayerCharacter* Player);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void InteractWith(APlayerCharacter* Player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PickUp(APlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	void Inspect(APlayerCharacter* Player);

public:

	UFUNCTION(BlueprintCallable)
	void DropItem();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item")
	FItemDetailStruct ItemDetails;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class USphereComponent* ItemInteractCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class UStaticMeshComponent* ItemMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FTransform ItemWorldPosition;

	//Does actor is rotating during inspection 
	UPROPERTY(BlueprintReadWrite)
	bool isRotating;
};
