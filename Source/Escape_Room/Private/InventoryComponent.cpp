// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Items.SetNum(SlotsAmount);
	OnInventoryUpdated.Broadcast();
	// ...
	
}

bool UInventoryComponent::AddItem(FItemDetailStruct ItemStruct)
{
	if (Items.FindByPredicate([](FItemDetailStruct n) { return (n.ItemMesh == nullptr) ? true : false; }))
	{
		Items.FindByPredicate([](FItemDetailStruct n) { return (n.ItemMesh == nullptr) ? true : false; })[0] = ItemStruct;
		OnInventoryUpdated.Broadcast();
		return true;
	}
	
	//TODO make pop-up "You have no inventory space left!"
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("You dont have any inventory space left!"));
	return false;
}

bool UInventoryComponent::RemoveItem(FItemDetailStruct ItemStruct)
{
	Items[Items.Find(ItemStruct)] = FItemDetailStruct();
	OnInventoryUpdated.Broadcast();
	/*if (Item)
	{
		//Item->OwnerInventory = nullptr;
		Items.Remove(Item);
		
		//Item->Destroy();
	}*/

	return true;
}
