// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

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

void APuzzle::ChangeView()
{
	auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	AActor* From;
	AActor* To;

	if (Player->State == EPlayerCharacterState::None)
	{
		From = Cast<AActor>(Player);
		To = Cast<AActor>(this);

		Controller->bShowMouseCursor = true;
		FInputModeGameAndUI InputMode = FInputModeGameAndUI();
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		Controller->SetInputMode(InputMode);
		Player->State = EPlayerCharacterState::Puzzle;
	}
	else
	{
		From = Cast<AActor>(this);
		To = Cast<AActor>(Player);

		Controller->bShowMouseCursor = false;
		Controller->SetInputMode(FInputModeGameOnly());
		Controller->SetIgnoreLookInput(false);
		Player->State = EPlayerCharacterState::None;
	}

	Controller->SetViewTargetWithBlend(To, 0.5f);
	From->DisableInput(Controller);
	To->EnableInput(Controller);
}
