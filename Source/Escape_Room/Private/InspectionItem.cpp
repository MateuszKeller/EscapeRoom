// Fill out your copyright notice in the Description page of Project Settings.


#include "InspectionItem.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInspectionItem::AInspectionItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInspectionItem::BeginPlay()
{
	Super::BeginPlay();

	ItemWorldPosition = this->GetActorTransform();
}


void AInspectionItem::OnLookAt_Implementation(APlayerCharacter* Player)
{
	if (Player->bShowOutline)
	{
		ItemMeshComponent->SetRenderCustomDepth(true);
	}
	else
	{
	Player->OnMessageUpdate.Broadcast(Message);
	}
}

void AInspectionItem::OnInteract_Implementation(APlayerCharacter* Player)
{
	Player->OnMessageUpdate.Broadcast(FText::FromString(""));
	this->Inspect(Player);
}

void AInspectionItem::OnStopLooking_Implementation()
{
	ItemMeshComponent->SetRenderCustomDepth(false);
}

void AInspectionItem::DropItem()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Hehe I'm free!"));

	
	//DetachFromActor(rules);
	
	//FVector GripReset = ItemMeshComponent->GetRelativeLocation(); 
	//FVector GripReset = ItemMeshComponent->GetComponentLocation();

	//GripReset.Z *= -1;
	//GripPoint->SetRelativeLocation(GripReset);
	//GripPoint->SetWorldLocation(GripReset);
	//GripPoint->SetRelativeRotation(FRotator(0.f));

	FDetachmentTransformRules rules = FDetachmentTransformRules(EDetachmentRule::KeepRelative, true);
	//FDetachmentTransformRules rules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, true);
	GripPoint->DetachFromComponent(rules);
	GripPoint->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false));
	this->SetActorTransform(ItemWorldPosition);
	this->SetActorEnableCollision(true);
	GripPoint->SetRelativeLocation(ItemMeshComponent->GetRelativeLocation() * -1);
	//ItemMesh->SetSimulatePhysics(true);

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	Controller->bShowMouseCursor = false;
	Controller->SetInputMode(FInputModeGameOnly());

	Player->HoldItem = nullptr;
	this->DisableInput(Controller);
	Player->EnableInput(Controller);
	Player->State = EPlayerCharacterState::None;
	this->bIsRotating = false;

}