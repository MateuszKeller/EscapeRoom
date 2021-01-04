// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "AdvancedPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API AAdvancedPuzzle : public APuzzle
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AAdvancedPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent();

	//Moving forward and backward
	UFUNCTION()
	void Turn(float Value);

	//Moving left and right
	UFUNCTION()
	void LookUp(float Value);

	void ToggleRotation();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* CameraRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APuzzlePart*> PuzzleParts;

	//Does actor is rotating during inspection 
	UPROPERTY(BlueprintReadWrite)
	bool bIsRotating = false;

};
