// Fill out your copyright notice in the Description page of Project Settings.


#include "Rods.h"
#include "Others.h"
#include "PlayerCharacter.h"

// Sets default values
ARods::ARods()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Sphere"));
	RootComponent = InteractCollision;*/

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetupAttachment(PuzzleMesh);
	PuzzleCamera->SetupAttachment(Base);
	Handle->SetupAttachment(Base);

	Rod_0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_0"));
	Rod_0->SetupAttachment(Handle);
	Rod_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_1"));
	Rod_1->SetupAttachment(Handle);
	Rod_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_2"));
	Rod_2->SetupAttachment(Handle);
	Rod_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_3"));
	Rod_3->SetupAttachment(Handle);
	Rod_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_4"));
	Rod_4->SetupAttachment(Handle);

	Base->SetCustomDepthStencilValue(2);
	Rod_0->SetCustomDepthStencilValue(2);
	Rod_1->SetCustomDepthStencilValue(2);
	Rod_2->SetCustomDepthStencilValue(2);
	Rod_3->SetCustomDepthStencilValue(2);
	Rod_4->SetCustomDepthStencilValue(2);


	Colors.Empty();
	Highlights.Empty();
	Current.Empty();
	Solution.Empty();
	

	Colors.Add(FColor::Black);
	Highlights.Add(FColor::White);

	Current.Add(Rod_0, 0);
	Current.Add(Rod_1, 0);
	Current.Add(Rod_2, 0);
	Current.Add(Rod_3, 0);
	Current.Add(Rod_4, 0);

	Solution.Add(Rod_0, 1);
	Solution.Add(Rod_1, 0);
	Solution.Add(Rod_2, 0);
	Solution.Add(Rod_3, 0);
	Solution.Add(Rod_4, 0);
}

// Called when the game starts or when spawned
void ARods::BeginPlay()
{
	Super::BeginPlay();
	
	Rod_0->OnClicked.AddDynamic(this, &ARods::ChangeColor);
	Rod_0->OnBeginCursorOver.AddDynamic(this, &ARods::OnStartHover);
	Rod_0->OnEndCursorOver.AddDynamic(this, &ARods::OnEndHover);

	Rod_1->OnClicked.AddDynamic(this, &ARods::ChangeColor);
	Rod_1->OnBeginCursorOver.AddDynamic(this, &ARods::OnStartHover);
	Rod_1->OnEndCursorOver.AddDynamic(this, &ARods::OnEndHover);

	Rod_2->OnClicked.AddDynamic(this, &ARods::ChangeColor);
	Rod_2->OnBeginCursorOver.AddDynamic(this, &ARods::OnStartHover);
	Rod_2->OnEndCursorOver.AddDynamic(this, &ARods::OnEndHover);

	Rod_3->OnClicked.AddDynamic(this, &ARods::ChangeColor);
	Rod_3->OnBeginCursorOver.AddDynamic(this, &ARods::OnStartHover);
	Rod_3->OnEndCursorOver.AddDynamic(this, &ARods::OnEndHover);

	Rod_4->OnClicked.AddDynamic(this, &ARods::ChangeColor);
	Rod_4->OnBeginCursorOver.AddDynamic(this, &ARods::OnStartHover);
	Rod_4->OnEndCursorOver.AddDynamic(this, &ARods::OnEndHover);
}

// Called every frame
void ARods::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ARods::IsSolved_Implementation()
{
	for (auto Elem : Solution)
	{
		if (Elem.Value != Current[Elem.Key])
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Rods.cpp - Solution: %s %i"), *Elem.Key->GetName(), Elem.Value));
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Rods.cpp - Current: %i"), Current[Elem.Key]));
			return false;
		}
	}

	return true;
}

void ARods::ChangeColor(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player->State == EPlayerCharacterState::Puzzle)
	{
		int32 ColorNumber = Current[Cast<UStaticMeshComponent>(TouchedComponent)];
		ColorNumber++;
		ColorNumber %= Colors.Num();

		Current.Add(Cast<UStaticMeshComponent>(TouchedComponent), ColorNumber);
		ChangeMaterial(Cast<UStaticMeshComponent>(TouchedComponent), Colors[ColorNumber], Highlights[ColorNumber]);

		if (IsSolved())
		{
			OnSolve();
			bIsSolved = true;
		}
	}
	
}

void ARods::ShowOutline(bool Yes)
{
	Base->SetRenderCustomDepth(Yes);
	Rod_0->SetRenderCustomDepth(Yes);
	Rod_1->SetRenderCustomDepth(Yes);
	Rod_2->SetRenderCustomDepth(Yes);
	Rod_3->SetRenderCustomDepth(Yes);
	Rod_4->SetRenderCustomDepth(Yes);
}
