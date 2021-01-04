// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Engine/StaticMesh.h"
#include "Item.generated.h"

class APlayerCharacter;

UCLASS(ABSTRACT)
class ESCAPE_ROOM_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent();

	//Moving forward and backward
	UFUNCTION()
	void Turn(float Value);
	//Moving left and right
	UFUNCTION()
	void LookUp(float Value);

	void ToggleRotation();


	UFUNCTION(BlueprintCallable)
	void Inspect(APlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	virtual	void DropItem();

public:

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class UCapsuleComponent* ItemInteractCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class UStaticMeshComponent* ItemMeshComponent;

	//Does actor is rotating during inspection 
	UPROPERTY(BlueprintReadWrite)
	bool bIsRotating = false;

};
