// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"
#include "PlayerCharacter.h"


// Sets default values
APickupItem::APickupItem()
{

}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
}

void APickupItem::OnLookAt_Implementation(APlayerCharacter* Player)
{
	if (!bInsideInventory)
	{
		ItemMeshComponent->SetRenderCustomDepth(true);
		Player->OnPointerTextUpdate.Broadcast(ItemDetails.Message);
	}
}

void APickupItem::OnInteract_Implementation(APlayerCharacter* Player)
{
	OnStopLooking();
	Player->OnPointerTextUpdate.Broadcast(FText::FromString(""));
	Take(Player);
}

void APickupItem::OnStopLooking_Implementation()
{
	ItemMeshComponent->SetRenderCustomDepth(false);
}