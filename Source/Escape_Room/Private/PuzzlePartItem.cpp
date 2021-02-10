// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePartItem.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APuzzlePartItem::APuzzlePartItem()
{

}

// Called when the game starts or when spawned
void APuzzlePartItem::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddDynamic(this, &APuzzlePartItem::OnClickedTake);
	OnBeginCursorOver.AddDynamic(this, &APuzzlePartItem::OnStartHover);
	OnEndCursorOver.AddDynamic(this, &APuzzlePartItem::OnEndHover);
}

void APuzzlePartItem::OnClickedTake(AActor* TouchedActor, FKey ButtonPressed)
{
	if (!bInsideInventory && IsNotWalking())
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->CurrentMouseCursor = EMouseCursor::Default;
		ItemMeshComponent->SetRenderCustomDepth(false);
		Take(Player);
	}
}

void APuzzlePartItem::OnStartHover(AActor* TouchedActor)
{
	if (!bInsideInventory && IsNotWalking())
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->CurrentMouseCursor = EMouseCursor::Hand;
		ItemMeshComponent->SetRenderCustomDepth(true);
		
		//APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		//Player->OnMessageUpdate.Broadcast(ItemDetails.Message);
	}
}

void APuzzlePartItem::OnEndHover(AActor* TouchedActor)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->CurrentMouseCursor = EMouseCursor::Default;
	ItemMeshComponent->SetRenderCustomDepth(false);
	//APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//Player->OnMessageUpdate.Broadcast(FText::FromString(""));
}
