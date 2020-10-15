// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// Sets default values
APuzzle::APuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Sphere"));
	RootComponent = InteractCollision;

	PuzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Puzzle Mesh"));
	PuzzleMesh->SetupAttachment(RootComponent);

	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	CameraRoot->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CameraRoot);

	PuzzleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PuzzleCamera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APuzzle::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void APuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzle::OnLookAt_Implementation(APlayerCharacter* Player) { }

void APuzzle::InteractWith_Implementation(APlayerCharacter* Player){ }

void APuzzle::ChangeView(AActor* From, AActor* To)
{
	auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Controller->SetViewTargetWithBlend(To, 0.5f);
	From->DisableInput(Controller);
	To->EnableInput(Controller);
	if (this == To)
	{
		Controller->bShowMouseCursor = true;
		auto InputMode = FInputModeGameAndUI();
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		Controller->SetInputMode(InputMode);
	}
	else
	{
		Controller->bShowMouseCursor = false;
		Controller->SetInputMode(FInputModeGameOnly());
	}
}
