// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedPuzzle.h"

// Sets default values
AAdvancedPuzzle::AAdvancedPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	CameraRoot->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CameraRoot);

	PuzzleCamera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AAdvancedPuzzle::BeginPlay()
{
	Super::BeginPlay();

	SetupPlayerInputComponent();

	//for (APuzzlePart* Part : PuzzleParts)
	//{
	//	if (IsValid(Part))
	//	{
	//		Part->OnSolve.AddDynamic(this, &APuzzle::TryToSolve);
	//	}
	//}	
}

// Called every frame
void AAdvancedPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAdvancedPuzzle::SetupPlayerInputComponent()
{
	Super::SetupPlayerInputComponent();
	EnableInput(GetWorld()->GetFirstPlayerController());

	if (this->InputComponent)
	{
		this->InputComponent->BindAction("RightClick", IE_Pressed, this, &AAdvancedPuzzle::ToggleRotation);
		this->InputComponent->BindAction("RightClick", IE_Released, this, &AAdvancedPuzzle::ToggleRotation);

		this->InputComponent->BindAxis("Turn", this, &AAdvancedPuzzle::Turn);
		this->InputComponent->BindAxis("LookUp", this, &AAdvancedPuzzle::LookUp);
	}
	DisableInput(GetWorld()->GetFirstPlayerController());
}

void AAdvancedPuzzle::Turn(float Value)
{
	if (bIsRotating)
	{
		CameraRoot->AddLocalRotation(FRotator(0, Value * 3.0, 0));
	}
}

void AAdvancedPuzzle::LookUp(float Value)
{
	if (bIsRotating)
	{
		SpringArm->AddLocalRotation(FRotator(Value * 3.0, 0, 0));
	}
}

void AAdvancedPuzzle::ToggleRotation()
{
	bIsRotating = !bIsRotating;
}

