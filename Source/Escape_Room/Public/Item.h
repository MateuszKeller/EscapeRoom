// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Engine/StaticMesh.h"
#include "Item.generated.h"

UCLASS()
class ESCAPE_ROOM_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnLookAt(APlayerCharacter* Player);
	virtual void OnLookAt_Implementation(APlayerCharacter* Player);

	//
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InteractWith(APlayerCharacter* Player);
	virtual void InteractWith_Implementation(APlayerCharacter* Player);

	//
	void PickUp(APlayerCharacter* Player);

	//
	void Inspect(APlayerCharacter* Player);

	//
	void Drop(APlayerCharacter* Player);

};
