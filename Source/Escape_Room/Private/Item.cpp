// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Sphere"));
	InteractCollision->SetupAttachment(RootComponent);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	WorldPosition = this->GetActorTransform();	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnLookAt_Implementation(APlayerCharacter * Player){ }

void AItem::StopLookAt_Implementation(APlayerCharacter* Player){ }

void AItem::InteractWith_Implementation(APlayerCharacter * Player)
{
	if (!IsValid(Player->HoldItem))
	{
		PickUp(Player);
	}
	else
	{
		Inspect(Player);
	}
}

void AItem::PickUp(APlayerCharacter* Player)
{
	ItemMesh->SetSimulatePhysics(false);
	this->SetActorEnableCollision(false);

	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
	AttachToComponent(Player->ItemGrip, rules);
	
	//InteractCollision->SetSimulatePhysics(false);
	
	Player->HoldItem = this;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Can't touch me!"));
}

void AItem::Inspect(APlayerCharacter* Player)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Inspection?!"));
	auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bShowMouseCursor = true;
	Player->DisableInput(Controller);
	this->EnableInput(Controller);

}

void AItem::Drop()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Hehe I'm free!"));
	
	FDetachmentTransformRules rules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, true);
	DetachFromActor(rules);
	this->SetActorTransform(WorldPosition);
	this->SetActorEnableCollision(true);
	//ItemMesh->SetSimulatePhysics(true);

	auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->bShowMouseCursor = false;
	Player->HoldItem = nullptr;
	this->DisableInput(Controller);
	Player->EnableInput(Controller);

	//Player->HoldItem = nullptr;
}
