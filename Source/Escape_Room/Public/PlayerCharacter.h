// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Others.h"
#include "PlayerCharacter.generated.h"

class AItem;

//UENUM(BlueprintType)
//enum class EPlayerState : uint8 {
//	None,
//	Inspecting,
//	Puzzle
//};


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
	
	AActor* LookAtActor;

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

	//Checking at what player is looking
	UFUNCTION(BlueprintCallable)
	AActor* CheckLookAt();

	//
	void Cancel();

	UPROPERTY(BlueprintReadWrite)
	AItem* HoldItem;

	UPROPERTY(EditAnywhere)
	USceneComponent* ItemGrip;

	UPROPERTY(EditAnywhere)
	float TraceDistance;

	UPROPERTY(BlueprintReadWrite)
	EPlayerCharacterState State = EPlayerCharacterState::None;



};
