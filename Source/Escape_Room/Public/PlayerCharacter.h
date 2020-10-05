// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ESCAPE_ROOM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere)
	USceneComponent* ItemGrip;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Moving forward and backward
	UFUNCTION()
	void MoveForward(float Value);

	//Moving left and right
	UFUNCTION()
	void MoveRight(float Value);

	//Interacting with actor
	UFUNCTION()
	void Interaction();

};
