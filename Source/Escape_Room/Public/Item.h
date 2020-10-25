// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Item.generated.h"

UCLASS()
class ESCAPE_ROOM_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///IInteractable:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void OnLookAt(APlayerCharacter* Player);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void InteractWith(APlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	void Drop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class USphereComponent* ItemInteractCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FTransform ItemWorldPosition;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item")
	FString ItemName = "Default Item";

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item")
	class UTexture2D* ItemThumbnail;

	//During inspection does actor is rotating
	UPROPERTY(BlueprintReadWrite)
	bool isRotating;

	UFUNCTION(BlueprintCallable)
	void PickUp(APlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	void Inspect(APlayerCharacter* Player);

};
