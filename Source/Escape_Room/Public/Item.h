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

	void RotationOn();
	void RotationOff();


	UFUNCTION(BlueprintCallable)
	void Inspect(APlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	virtual	void DropItem();

public:

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	USceneComponent* GripPoint;

	UPROPERTY(BlueprintReadWrite, Category = "Item")
	USceneComponent* PlayerGrip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FVector GripLocation = FVector(150.f, 0, 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UStaticMeshComponent* ItemMeshComponent;

	//Does actor is rotating during inspection 
	UPROPERTY(BlueprintReadWrite, Category = "Item")
	bool bIsRotating = false;
	
	//How fast item will rotate
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	float RotationMultiplier = 0.5;
		
};
