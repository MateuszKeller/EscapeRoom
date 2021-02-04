// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInventoryItem::AInventoryItem()
{

}

// Called when the game starts or when spawned
void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();

	if (!ItemDetails.ItemClass)
	{
		ItemDetails.ItemClass = this->GetClass();
	}
	ItemDetails.ItemMesh = ItemMeshComponent->GetStaticMesh();
	ItemDetails.ItemTransform = ItemMeshComponent->GetRelativeTransform();
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

void AInventoryItem::InspectFromInventory()
{
	bInsideInventory = true;
	Inspect(Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
}
void AInventoryItem::DropItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("InventoryItem.cpp - Go back to the Shadow!"));
	Destroy();
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	Player->HoldItem = nullptr;
	this->DisableInput(Controller);
	Player->EnableInput(Controller);
	Player->State = EPlayerCharacterState::None;
}

bool AInventoryItem::IsNotWalking()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	return Player->State == EPlayerCharacterState::Inspection || Player->State == EPlayerCharacterState::Puzzle ? true : false;
}