// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "InventoryComponent.h"
#include "Others.h"
#include "PlayerCharacter.generated.h"

//Delegate to bind BP to update message shown on UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageUpdate, FText, Message);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEyepieceUse);

UCLASS(ABSTRACT)
class ESCAPE_ROOM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	//Moving forward and backward
	UFUNCTION()
	void Turn(float Value);

	//Moving left and right
	UFUNCTION()
	void LookUp(float Value);


	//Interacting with actor
	UFUNCTION()
	void Interaction();

	//
	UFUNCTION()
	void ShowCursor();

	//Checking at what player is looking
	UFUNCTION(BlueprintCallable)
	AActor* CheckLookAt();

	void Eyepiece();

public:

	UFUNCTION(BlueprintCallable)
	void RemoveUsedItem();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnMessageUpdate OnMessageUpdate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEyepieceUse OnEyepieceUsed;

	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EPlayerCharacterState State = EPlayerCharacterState::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryComponent* PlayerInventory;


	AActor* LookAtActor = nullptr;

	UPROPERTY(BlueprintReadWrite)
	AItem* HoldItem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ItemGrip;
	
	UPROPERTY(EditAnywhere)
	float TraceDistance = 180.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasEyepiece = false;
};
