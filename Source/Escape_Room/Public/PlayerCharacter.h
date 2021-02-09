// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/PostProcessComponent.h"
#include "InventoryComponent.h"
#include "Others.h"
#include "PlayerCharacter.generated.h"

//Delegate to bind BP to update pointer text shown on UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPointerTextUpdate, FText, Message);

//Delegate to bind BP to update message shown on UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMessageUpdate, FText, Message, float, ShowTime);

//Delegate to bind BP to update keys helpers shown on UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKeysUpdate, FText, Message);

//Delegate to bind BP to update keys helpers shown on UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPointerUpdate);

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

public:

	UFUNCTION(BlueprintCallable)
	void Eyepiece();

	UFUNCTION(BlueprintCallable)
	void RemoveUsedItem();

	/// <summary>
	/// Delegates
	/// </summary>
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnPointerTextUpdate OnPointerTextUpdate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnMessageUpdate OnMessageUpdate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnKeysUpdate OnKeysUpdate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnPointerUpdate OnPointerUpdate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEyepieceUse OnEyepieceUsed;


	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere)
	UPostProcessComponent* EyepiceVision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EPlayerCharacterState State = EPlayerCharacterState::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryComponent* PlayerInventory;


	AActor* LookAtActor = nullptr;

	IInteractable* LastInteractable = nullptr;

	UPROPERTY(BlueprintReadWrite)
	AItem* HoldItem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ItemGrip;
	
	UPROPERTY(EditAnywhere)
	float TraceDistance = 180.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasEyepiece = false;
};
