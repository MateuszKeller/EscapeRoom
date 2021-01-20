// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Math/RotationMatrix.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Interactable.h"
#include "Item.h"

#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(RootComponent);

	ItemGrip = CreateDefaultSubobject<USceneComponent>(TEXT("ItemGrip"));
	ItemGrip->SetupAttachment(PlayerCamera);

	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* Controll = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!CheckLookAt() && !Controll->bShowMouseCursor)
	{
		if (bShowOutline && LastInteractable)
		{
			LastInteractable->Execute_OnStopLooking(LookAtActor);
		}
		else
		{
			OnMessageUpdate.Broadcast(FText::FromString(""));
		}
		
		LastInteractable = nullptr;
		LookAtActor = nullptr;
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interaction);
	PlayerInputComponent->BindAction("Cursor", IE_Pressed, this, &APlayerCharacter::ShowCursor);

	PlayerInputComponent->BindAction("Eyepiece", IE_Pressed, this, &APlayerCharacter::Eyepiece);
}

void APlayerCharacter::MoveForward(float Value)
{

	FVector Direction = FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void APlayerCharacter::Interaction()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("E - Pressed. Action!"));
	IInteractable* Interface = Cast<IInteractable>(LookAtActor);
	if (IsValid(LookAtActor))
	{
		Interface->Execute_OnInteract(LookAtActor, this);
	}
	else if(IsValid(HoldItem))
	{
		Interface->Execute_OnInteract(HoldItem, this);
	}
}

void APlayerCharacter::ShowCursor()
{
	APlayerController* Controll = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!Controll->bShowMouseCursor)
	{
		Controll->bShowMouseCursor = true;
		Controll->SetIgnoreLookInput(true);
			//Controll->SetIgnoreMoveInput(true);
		FInputModeGameAndUI InputMode = FInputModeGameAndUI();
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		InputMode.SetHideCursorDuringCapture(false);
		Controll->SetInputMode(InputMode);

		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		Controll->SetMouseLocation(ViewportSize.X / 2, ViewportSize.Y / 2);
	}
	else
	{
		Controll->bShowMouseCursor = false;
		Controll->SetIgnoreLookInput(false);
			//Controll->SetIgnoreMoveInput(false);
		FInputModeGameOnly InputMode = FInputModeGameOnly();
		Controll->SetInputMode(InputMode);
	}
}

AActor* APlayerCharacter::CheckLookAt()
{
	if (State != EPlayerCharacterState::None) return nullptr;

	FVector CameraLocation;
	FRotator CameraRotation;
	FHitResult Hit;

	GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
	FVector End = CameraLocation + (CameraRotation.Vector() * TraceDistance);

	FCollisionQueryParams Params;
	GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECC_Camera, Params);
	
	AActor* HitActor = Hit.GetActor();
	if (IsValid(HitActor))
	{
		bool bInteractable = HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass());
		if (bInteractable)
		{
			IInteractable* Interface = Cast<IInteractable>(LookAtActor);
			if (LookAtActor != HitActor)
			{
				LookAtActor = HitActor;
				LastInteractable = Cast<IInteractable>(LookAtActor);
				Interface->Execute_OnLookAt(LookAtActor, this);
				return LookAtActor;
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("LookAtActor != HitActor"));
			}
		}
		else
		{
			return nullptr;
			//LookAtActor = nullptr;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("!bInteractable"));
		}
	}
	else
	{
		return nullptr;
		//LookAtActor = nullptr;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("IsNotValid(HitActor)"));
	}
	return LookAtActor;
}

void APlayerCharacter::RemoveUsedItem()
{
	PlayerInventory->RemoveItem(PlayerInventory->CurrentlyUsedItem);
	PlayerInventory->CurrentlyUsedItem = FItemDetailStruct();
	OnMessageUpdate.Broadcast(FText::FromString(""));
}

void APlayerCharacter::Eyepiece()
{
	if (bHasEyepiece)
	{
		OnEyepieceUsed.Broadcast();
	}
}