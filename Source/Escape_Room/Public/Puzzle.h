// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interactable.h"
#include "Puzzle.generated.h"



UCLASS()
class ESCAPE_ROOM_API APuzzle : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* CameraRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* PuzzleCamera;

	UPROPERTY(EditAnywhere)
	USphereComponent* InteractCollision;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PuzzleMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///Interactable:
	//
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void OnLookAt(APlayerCharacter* Player);
	virtual void OnLookAt_Implementation(APlayerCharacter* Player);

	//
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void InteractWith(APlayerCharacter* Player);
	virtual void InteractWith_Implementation(APlayerCharacter* Player);

	//
	UFUNCTION(BlueprintCallable)
	void ChangeView(AActor* From, AActor* To);

};
