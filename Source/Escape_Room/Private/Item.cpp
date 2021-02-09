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

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent->SetMobility(EComponentMobility::Movable);

	GripPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Grip Point"));
	GripPoint->SetupAttachment(RootComponent);

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMeshComponent->SetupAttachment(GripPoint);
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
		this->InputComponent->BindAction("Rotate", IE_Pressed, this, &AItem::RotationOn);
		this->InputComponent->BindAction("Rotate", IE_Released, this, &AItem::RotationOff);

		this->InputComponent->BindAxis("Turn", this, &AItem::Turn);
		this->InputComponent->BindAxis("LookUp", this, &AItem::LookUp);

		this->InputComponent->BindAction("Eyepiece", IE_Pressed, this, &AItem::Eyepiece);
	}
	DisableInput(GetWorld()->GetFirstPlayerController());
}


void AItem::Turn(float Value)
{
	if (bIsRotating)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Turn"));
		GripPoint->AddLocalRotation(FRotator(0.0f, Value * RotationMultiplier, 0.0f));
		//RootComponent->AddLocalRotation(FRotator(0, Value * RotationMultiplier, 0));
	}
}

void AItem::LookUp(float Value)
{
	if (bIsRotating)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("LookUp"));
		PlayerGrip->AddLocalRotation(FRotator(Value * RotationMultiplier, 0.0f, 0.0f));

	}
}

void AItem::ToggleRotation()
{
	bIsRotating = !bIsRotating;
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("Item.cpp - %s"), bIsRotating ? TEXT("true") : TEXT("false")));
}

void AItem::RotationOn() 
{
	/*APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bShowMouseCursor = false;*/
	bIsRotating = true;
}
void AItem::RotationOff() 
{
	/*APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bShowMouseCursor = true;*/
	bIsRotating = false; 
}

void AItem::Inspect(APlayerCharacter* Player)
{
	bIsRotating = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Inspection?!"));
	//ItemMeshComponent->SetSimulatePhysics(false);
	//this->SetActorEnableCollision(false);

	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, false);
	PlayerGrip = Player->ItemGrip;
	PlayerGrip->SetRelativeLocation(GripLength);
	GripPoint->AttachToComponent(Player->ItemGrip, rules);
	//AttachToComponent(Player->ItemGrip, rules);

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
	ItemMeshComponent->SetRenderCustomDepth(false);
	Player->OnPointerUpdate.Broadcast();
	Player->OnKeysUpdate.Broadcast(FText::FromString("[LBM] Interaction\n[PPM] Rotation"));
}

void AItem::DropItem()
{
	PlayerGrip = nullptr;
}

void AItem::Eyepiece()
{
	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Eyepiece();
}