// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ItemInteractCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Interaction Capsule"));
	ItemInteractCollision->InitCapsuleSize(32.f, 32.f);
	ItemInteractCollision->SetupAttachment(RootComponent);

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();	

	SetupPlayerInputComponent();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::SetupPlayerInputComponent()
{
	EnableInput(GetWorld()->GetFirstPlayerController());

	if (this->InputComponent)
	{
		this->InputComponent->BindAction("Interact", IE_Pressed, this, &AItem::DropItem);
		this->InputComponent->BindAction("RightClick", IE_Pressed, this, &AItem::ToggleRotation);
		this->InputComponent->BindAction("RightClick", IE_Released, this, &AItem::ToggleRotation);

		this->InputComponent->BindAxis("Turn", this, &AItem::Turn);
		this->InputComponent->BindAxis("LookUp", this, &AItem::LookUp);
	}
	DisableInput(GetWorld()->GetFirstPlayerController());
}


void AItem::Turn(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Turn"));
	if (bIsRotating)
	{
		RootComponent->AddLocalRotation(FRotator(0, Value * 3.0, 0));
	}
}

void AItem::LookUp(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("LookUp"));
	if (bIsRotating)
	{
		RootComponent->AddLocalRotation(FRotator(Value * 3.0, 0, 0));
	}
}

void AItem::ToggleRotation()
{
	bIsRotating = !bIsRotating;
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("Item.cpp - %s"), bIsRotating ? TEXT("true") : TEXT("false")));
}

void AItem::Inspect(APlayerCharacter* Player)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Inspection?!"));
	ItemMeshComponent->SetSimulatePhysics(false);
	this->SetActorEnableCollision(false);

	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
	AttachToComponent(Player->ItemGrip, rules);
	//InteractCollision->SetSimulatePhysics(false);
	
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bShowMouseCursor = true;
	FInputModeGameAndUI InputMode = FInputModeGameAndUI();
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
	Controller->SetInputMode(InputMode);

	Player->HoldItem = this;
	Player->DisableInput(Controller);
	this->EnableInput(Controller);
	Player->State = EPlayerCharacterState::Inspection;
}

void AItem::DropItem()
{

}