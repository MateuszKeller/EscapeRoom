// Fill out your copyright notice in the Description page of Project Settings.


#include "Rods.h"

// Sets default values
ARods::ARods()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Sphere"));
	RootComponent = InteractCollision;*/

	Rod_0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_0"));
	Rod_0->SetupAttachment(RootComponent);
	Rod_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_1"));
	Rod_1->SetupAttachment(RootComponent);
	Rod_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_2"));
	Rod_2->SetupAttachment(RootComponent);
	Rod_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_3"));
	Rod_3->SetupAttachment(RootComponent);
	Rod_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rod_4"));
	Rod_4->SetupAttachment(RootComponent);

	Colors.Add(FColor::White);

	Current.Add(Rod_0, 0);
	Current.Add(Rod_1, 0);
	Current.Add(Rod_2, 0);
	Current.Add(Rod_3, 0);
	Current.Add(Rod_4, 0);

	Solution.Add(Rod_0, 0);
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
	Rod_1->OnClicked.AddDynamic(this, &ARods::ChangeColor);
	Rod_2->OnClicked.AddDynamic(this, &ARods::ChangeColor);
	Rod_3->OnClicked.AddDynamic(this, &ARods::ChangeColor);
	Rod_4->OnClicked.AddDynamic(this, &ARods::ChangeColor);
}

// Called every frame
void ARods::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ARods::IsSolved()
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
	int32 ColorNumber = Current[Cast<UStaticMeshComponent>(TouchedComponent)];
	ColorNumber++;
	ColorNumber %= Colors.Num();

	Current.Add(Cast<UStaticMeshComponent>(TouchedComponent), ColorNumber);
	ChangeMaterial(Cast<UStaticMeshComponent>(TouchedComponent), Colors[ColorNumber]);

	if (IsSolved())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("Rods.cpp - SOLVED")));
		OnSolve();
		bIsSolved = true;
	}
}
