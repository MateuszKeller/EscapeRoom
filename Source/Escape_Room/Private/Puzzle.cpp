// Fill out your copyright notice in the Description page of Project Settings.

#include "Puzzle.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APuzzle::APuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Sphere"));
	RootComponent = InteractCollision;*/

	PuzzleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Puzzle Mesh"));
	PuzzleMesh->SetupAttachment(RootComponent);

	/*CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	CameraRoot->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CameraRoot);*/

	PuzzleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PuzzleCamera->SetupAttachment(PuzzleMesh);

	Handle = CreateDefaultSubobject<USceneComponent>(TEXT("Parts Handle"));
	Handle->SetupAttachment(PuzzleMesh);

	PuzzleMesh->SetCustomDepthStencilValue(2);
}

// Called when the game starts or when spawned
void APuzzle::BeginPlay()
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

		this->InputComponent->BindAction("Eyepiece", IE_Pressed, this, &APuzzle::Eyepiece);
	}
	DisableInput(GetWorld()->GetFirstPlayerController());
}

void APuzzle::OnLookAt_Implementation(APlayerCharacter* Player)
{
	if (!bIsSolved)
	{
		PuzzleMesh->SetRenderCustomDepth(true);
		Player->OnPointerTextUpdate.Broadcast(Message);
	}
}

void APuzzle::OnInteract_Implementation(APlayerCharacter* Player)
{
	if(!bIsSolved)
	{
		OnStopLooking();
		Player->OnPointerTextUpdate.Broadcast(FText::FromString(""));
		ChangeView();
	}
}

void APuzzle::OnStopLooking_Implementation()
{
	PuzzleMesh->SetRenderCustomDepth(false);
}

void APuzzle::OnStartHover(UPrimitiveComponent* TouchedComponent)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player->State == EPlayerCharacterState::Puzzle)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->CurrentMouseCursor = EMouseCursor::Hand;
	}
}

void APuzzle::OnEndHover(UPrimitiveComponent* TouchedComponent)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->CurrentMouseCursor = EMouseCursor::Default;
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
		InputMode.SetHideCursorDuringCapture(false);
		Controller->SetInputMode(InputMode);
		//Controller->SetIgnoreLookInput(true);
		Player->State = EPlayerCharacterState::Puzzle;

		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		Controller->SetMouseLocation(ViewportSize.X / 2, ViewportSize.Y / 2);
		Player->OnKeysUpdate.Broadcast(FText::FromString("[LBM] Interaction\n[E]/[ESC] Exit Puzzle"));
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
		Player->OnKeysUpdate.Broadcast(FText::FromString(""));
	}

	Player->OnPointerUpdate.Broadcast();
	Controller->SetViewTargetWithBlend(To, Time);
	From->DisableInput(Controller);
	To->EnableInput(Controller);
}

bool APuzzle::IsSolved_Implementation()
{
	return bIsSolved;
}

void APuzzle::Eyepiece()
{
	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Eyepiece();
}

//void APuzzle::TryToSolve()
//{
//	for (APuzzlePart* Part : PuzzleParts)
//	{
//		if (!Part->bIsSolved) return;
//	}
//	bIsSolved = true;
//
//	for (APuzzleAnswerer* Answerer : PuzzleAnswerers)
//	{
//		Answerer->Answer();
//	}
//}



