// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemComponent.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	ItemDetails.ItemMesh = GetStaticMesh();
	// ...
	
}


// Called every frame
void UItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UItemComponent::PickUp(APlayerCharacter* Player)
{
	if (Player->State == EPlayerCharacterState::Puzzle)
	{
		if (Player->PlayerInventory->AddItem(ItemDetails))
		{
			DestroyComponent();
			return true;
		}
		
		
	}

	return false;
}