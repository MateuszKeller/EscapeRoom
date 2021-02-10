// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePart.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
APuzzlePart::APuzzlePart()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	PuzzlePartInteractCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Interaction Capsule"));
	PuzzlePartInteractCollision->InitCapsuleSize(32.f, 32.f);
	PuzzlePartInteractCollision->SetupAttachment(RootComponent);

	PuzzlePartMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	PuzzlePartMeshComponent->SetupAttachment(RootComponent);

	PuzzlePartMeshComponent->SetCustomDepthStencilValue(6);
}

// Called when the game starts or when spawned
void APuzzlePart::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddDynamic(this, &APuzzlePart::OnClickedTake);
	OnBeginCursorOver.AddDynamic(this, &APuzzlePart::OnStartHover);
	OnEndCursorOver.AddDynamic(this, &APuzzlePart::OnEndHover);
}

// Called every frame
void APuzzlePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzlePart::Solve_Implementation()
{
	bIsSolved = true;
	OnSolve.Broadcast();
}

void APuzzlePart::OnClickedTake(AActor* TouchedActor, FKey ButtonPressed)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!bIsSolved && PlayerController->bShowMouseCursor)
	{
		PlayerController->CurrentMouseCursor = EMouseCursor::Default;
	}
}

void APuzzlePart::OnStartHover(AActor* TouchedActor)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!bIsSolved && PlayerController->bShowMouseCursor)
	{
		PlayerController->CurrentMouseCursor = EMouseCursor::Hand;
		PuzzlePartMeshComponent->SetRenderCustomDepth(true);
	}	
}

void APuzzlePart::OnEndHover(AActor* TouchedActor)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!bIsSolved && PlayerController->bShowMouseCursor)
	{
		PlayerController->CurrentMouseCursor = EMouseCursor::Default;
		PuzzlePartMeshComponent->SetRenderCustomDepth(false);
	}
}