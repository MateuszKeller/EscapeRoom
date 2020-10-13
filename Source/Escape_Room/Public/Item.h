// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Item.generated.h"

// TODO zmiana PickUp() na ~ToEquipment()
// TODO dodaæ 2 BP ~EquipableItem i ~InspectionableItem	
// TODO zmieniæ InteractWith na BP
	// EqItem bd mia³ na nim PickUp(), InsItem - Inspection()

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
	USphereComponent* InteractCollision;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
	FTransform WorldPosition;

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite)
	bool isRotating;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnLookAt(APlayerCharacter* Player);
	virtual void OnLookAt_Implementation(APlayerCharacter* Player);

	//
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void StopLookAt(APlayerCharacter* Player);
	virtual void StopLookAt_Implementation(APlayerCharacter* Player);

	//
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InteractWith(APlayerCharacter* Player);
	virtual void InteractWith_Implementation(APlayerCharacter* Player);

	//
	UFUNCTION()
	void PickUp(APlayerCharacter* Player);

	//
	UFUNCTION()
	void Inspect(APlayerCharacter* Player);

	//
	UFUNCTION(BlueprintCallable)
	void Drop();

};
