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

	SetupPlayerInputComponent();

	for (APuzzlePart* Part : PuzzleParts)
	{
		if (IsValid(Part))
		{
			Part->OnSolve.AddDynamic(this, &APuzzle::TryToSolve);
		}
	}	
}

// Called every frame
void APuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzle::SetupPlayerInputComponent()
{
	EnableInput(GetWorld()->GetFirstPlayerController());

	if (this->InputComponent)
	{
		this->InputComponent->BindAction("Interact", IE_Pressed, this, &APuzzle::ChangeView);
		this->InputComponent->BindAction("RightClick", IE_Pressed, this, &APuzzle::AllowRotation);
		this->InputComponent->BindAction("RightClick", IE_Released, this, &APuzzle::AllowRotation);

		this->InputComponent->BindAxis("Turn", this, &APuzzle::Turn);
		this->InputComponent->BindAxis("LookUp", this, &APuzzle::LookUp);
	}
	DisableInput(GetWorld()->GetFirstPlayerController());
}

void APuzzle::Turn(float Value)
{
	if (bIsRotating)
	{
		CameraRoot->AddLocalRotation(FRotator(0, Value * 3.0, 0));
	}
}

void APuzzle::LookUp(float Value)
{
	if (bIsRotating)
	{
		SpringArm->AddLocalRotation(FRotator(Value * 3.0, 0, 0));
	}
}

void APuzzle::AllowRotation()
{
	bIsRotating = !bIsRotating;
}

void APuzzle::OnLookAt_Implementation(APlayerCharacter* Player)
{
	Player->OnMessageUpdate.Broadcast(Message);
}

void APuzzle::OnInteract_Implementation(APlayerCharacter* Player)
{
	Player->OnMessageUpdate.Broadcast(FText::FromString(""));
	ChangeView();
}

void APuzzle::ChangeView()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	AActor* From;
	AActor* To;

	if (Player->State == EPlayerCharacterState::None)
	{
		From = Cast<AActor>(Player);
		From->SetActorTickEnabled(false);
		To = Cast<AActor>(this);

		
		Controller->bShowMouseCursor = true;
		FInputModeGameAndUI InputMode = FInputModeGameAndUI();
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		//InputMode.SetHideCursorDuringCapture(false);
		Controller->SetInputMode(InputMode);
		Player->State = EPlayerCharacterState::Puzzle;

		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		Controller->SetMouseLocation(ViewportSize.X / 2, ViewportSize.Y / 2);
	}
	else
	{
		From = Cast<AActor>(this);
		To = Cast<AActor>(Player);
		To->SetActorTickEnabled(true);

		Controller->bShowMouseCursor = false;
		Controller->SetInputMode(FInputModeGameOnly());
		Controller->SetIgnoreLookInput(false);
		Player->State = EPlayerCharacterState::None;
	}

	Controller->SetViewTargetWithBlend(To, 0.5f);
	From->DisableInput(Controller);
	To->EnableInput(Controller);
}

void APuzzle::TryToSolve()
{
	for (APuzzlePart* Part : PuzzleParts)
	{
		if (!Part->bIsSolved) return;
	}
	bIsSolved = true;

	for (APuzzleAnswerer* Answerer : PuzzleAnswerers)
	{
		Answerer->Answer();
	}
}



