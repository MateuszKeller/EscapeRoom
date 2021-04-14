// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemComponent.h"
#include "PlayerCharacter.h"
#include "PuzzlePart.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UItemComponent::CheckUsedItem()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	auto Item = Player->PlayerInventory->CurrentlyUsedItem;
	//bool bIsCorrectItem = (KeyItemClass == Player->PlayerInventory->CurrentlyUsedItem.ItemClass ? true : false);
		
	for (auto KeyItemClass : KeyItemClasses)
	{
		if (KeyItemClass == Item.ItemClass)
		{
			ItemClass = Item.ItemClass;
			DummyMesh = Item.ItemMesh;
			MaterialInterface = Item.ItemMesh->GetMaterial(0);
			Scale = Item.ItemTransform.GetScale3D();
			ItemName = Item.ItemName;

			if (Cast<APuzzlePart>(GetOwner()))
			{
				Cast<APuzzlePart>(GetOwner())->Solve();
			}
			
			Player->RemoveUsedItem();
			return true;
		}
	}
	Player->OnMessageAnimation.Broadcast(FText::FromString("Incorrect Item"), 1.5f);
	return false;
}

