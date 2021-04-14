// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interactable.h"
#include "PuzzlePart.h"
#include "PuzzleAnswerer.h"
#include "Kismet/GameplayStatics.h"
#include "Puzzle.generated.h"

class APlayerCharacter;

UCLASS(ABSTRACT)
class ESCAPE_ROOM_API APuzzle : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent();

	///IInteractable:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnLookAt(APlayerCharacter* Player);
	virtual void OnLookAt_Implementation(APlayerCharacter* Player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(APlayerCharacter* Player);
	virtual void OnInteract_Implementation(APlayerCharacter* Player);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnStopLooking();
	virtual void OnStopLooking_Implementation();

	UFUNCTION()
	void OnStartHover(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void OnEndHover(UPrimitiveComponent* TouchedComponent);


	// Changes view from player to puzzle and vice versa
	UFUNCTION(BlueprintCallable)
	void ChangeView();

	//
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsSolved();
	virtual bool IsSolved_Implementation();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void OnSolve();

	void Eyepiece();

	virtual void ShowOutline(bool Yes);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* PuzzleCamera;

	/*UPROPERTY(EditAnywhere)
	USphereComponent* InteractCollision;*/

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PuzzleMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Handle;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APuzzleAnswerer*> PuzzleAnswerers;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	FText Message = FText::FromString("[E] Solve");

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	bool bIsSolved = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float Time = 0.5;
};
