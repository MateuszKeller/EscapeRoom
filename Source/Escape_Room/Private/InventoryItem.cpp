// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"
#include "PlayerCharacter.h"


// Sets default values
AInventoryItem::AInventoryItem()
{

}

// Called when the game starts or when spawned
void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();

	ItemDetails.ItemClass = this->GetClass();
	ItemDetails.ItemMesh = ItemMeshComponent->GetStaticMesh();
}

void AInventoryItem::Take(APlayerCharacter* Player)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Can't touch me!"));

	if(Player->PlayerInventory->AddItem(ItemDetails))
		this->Destroy();

	/*
	ItemMesh->SetSimulatePhysics(false);
	this->SetActorEnableCollision(false);

	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
	AttachToComponent(Player->ItemGrip, rules);
	//InteractCollision->SetSimulatePhysics(false);

	Player->HoldItem = this;*/
}

void AInventoryItem::DropItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Go back to the Shadow!"));
}