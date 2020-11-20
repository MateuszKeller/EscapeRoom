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
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Take(Player);

}

void APuzzlePartItem::OnStartHover(AActor* TouchedActor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->OnMessageUpdate.Broadcast(FText::FromString("[E] Take"));
}

void APuzzlePartItem::OnEndHover(AActor* TouchedActor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->OnMessageUpdate.Broadcast(FText::FromString(""));
}
