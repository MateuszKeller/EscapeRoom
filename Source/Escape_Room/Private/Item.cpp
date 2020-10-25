// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ItemInteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Sphere"));
	ItemInteractCollision->SetupAttachment(RootComponent);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();	

	ItemWorldPosition = this->GetActorTransform();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::PickUp(APlayerCharacter* Player)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Can't touch me!"));
	ItemMesh->SetSimulatePhysics(false);
	this->SetActorEnableCollision(false);

	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
	AttachToComponent(Player->ItemGrip, rules);
	//InteractCollision->SetSimulatePhysics(false);

	Player->HoldItem = this;
}

void AItem::Inspect(APlayerCharacter* Player)
{
	ItemMesh->SetSimulatePhysics(false);
	this->SetActorEnableCollision(false);

	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
	AttachToComponent(Player->ItemGrip, rules);
	//InteractCollision->SetSimulatePhysics(false);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Inspection?!"));

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

void AItem::Drop()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Hehe I'm free!"));
	
	FDetachmentTransformRules rules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, true);
	DetachFromActor(rules);
	this->SetActorTransform(ItemWorldPosition);
	this->SetActorEnableCollision(true);
	//ItemMesh->SetSimulatePhysics(true);

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bShowMouseCursor = false;
	Controller->SetInputMode(FInputModeGameOnly());

	Player->HoldItem = nullptr;
	this->DisableInput(Controller);
	Player->EnableInput(Controller);
	Player->State = EPlayerCharacterState::None;

}
