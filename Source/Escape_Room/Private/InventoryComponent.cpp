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
	FItemDetailStruct empty;
	//Item->OwnerInventory = this;
	Items.FindByPredicate([](FItemDetailStruct n) { return (n.ItemMesh == nullptr) ? true : false; })[0] = ItemStruct;
		
		//Items[Items.Find(empty.ItemMesh==nullptr)] = ItemStruct;
		
		//Items.Add(Item);

		OnInventoryUpdated.Broadcast();
	
	return true;
}

bool UInventoryComponent::RemoveItem(FItemDetailStruct ItemStruct)
{
	/*if (Item)
	{
		//Item->OwnerInventory = nullptr;
		Items.Remove(Item);
		OnInventoryUpdated.Broadcast();
		//Item->Destroy();
	}*/

	return true;
}
