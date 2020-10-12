// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
//#include "Engine/EngineTypes.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = nullptr;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnLookAt_Implementation(APlayerCharacter * Player)
{
}

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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Can't touch me!"));
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
	AttachToComponent(Player->ItemGrip, rules);
	this->SetActorEnableCollision(false);
	//RootComponent->SetSim
	Player->HoldItem = this;

		

		

}

void AItem::Inspect(APlayerCharacter* Player)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Can't look at me!"));

}

void AItem::Drop(APlayerCharacter* Player)
{

}
