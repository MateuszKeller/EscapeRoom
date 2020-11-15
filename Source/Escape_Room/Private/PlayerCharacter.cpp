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

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interaction);
	PlayerInputComponent->BindAction("Cancel", IE_Pressed, this, &APlayerCharacter::CancelInspection);
	PlayerInputComponent->BindAction("Cursor", IE_Pressed, this, &APlayerCharacter::ShowCursor);
	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerCharacter::TryToUse);


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

void APlayerCharacter::Interaction()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("E - Pressed. Action!"));
	IInteractable* Interface = Cast<IInteractable>(LookAtActor);
	if (IsValid(LookAtActor))
	{
		Interface->Execute_InteractWith(LookAtActor, this);
	}
	else if(IsValid(HoldItem))
	{
		Interface->Execute_InteractWith(HoldItem, this);
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
	FVector CameraLocation;
	FRotator CameraRotation;
	FHitResult Hit;

	GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
	FVector End = CameraLocation + (CameraRotation.Vector() * TraceDistance);

	FCollisionQueryParams Params;
	GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECC_Camera, Params);
	//DrawDebugLine(GetWorld(), CameraLocation, End, FColor::Orange, false, 2.0f);
	
	AActor* HitActor = Hit.GetActor();
	IInteractable* Interface = Cast<IInteractable>(LookAtActor);
	if (IsValid(HitActor))
	{
		bool bInteractable = HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass());	
		if (bInteractable)
		{
			if (LookAtActor != HitActor)
			{
				LookAtActor = HitActor;
				Interface->Execute_OnLookAt(LookAtActor, this);
			}
		}
	}
	else
	{
		LookAtActor = nullptr;
	}

	return LookAtActor;
}

void APlayerCharacter::CancelInspection()
{
	if (IsValid(HoldItem))
	{
		HoldItem->DropItem();
	}
}

/*void APlayerCharacter::UseItem(AItem* Item)
{
	if (Item)
	{
		Item->DropItem();
	}
}*/

void APlayerCharacter::TryToUse()
{
	APlayerController* Controll = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Try To Use"));
	if (!Controll->bShowMouseCursor) return;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Cursor"));
	if (PlayerInventory->CurrentlyUsedItem == FItemDetailStruct()) return;

	FString t = PlayerInventory->CurrentlyUsedItem.ItemName;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, t);

	FHitResult Hit;
	FActorSpawnParameters SpawnParams;

	Controll->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Location: %s"), *Hit.Location.ToString()));
	AItem* SpawnedActor = GetWorld()->SpawnActor<AItem>(PlayerInventory->CurrentlyUsedItem.ItemClass, Hit.Location, FRotator(), SpawnParams);
	SpawnedActor->ItemDetails = PlayerInventory->CurrentlyUsedItem;
	
	PlayerInventory->RemoveItem(PlayerInventory->CurrentlyUsedItem);
	
}
