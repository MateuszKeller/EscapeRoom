// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePart.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter.h"


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
}

// Called when the game starts or when spawned
void APuzzlePart::BeginPlay()
{
	Super::BeginPlay();
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