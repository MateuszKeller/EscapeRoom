// Fill out your copyright notice in the Description page of Project Settings.


#include "EyepieceStand.h"

// Sets default values
AEyepieceStand::AEyepieceStand()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Sphere"));
	RootComponent = InteractCollision;*/
	BasePart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Part"));
	BasePart->SetupAttachment(RootComponent);

	Part_0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part_0"));
	Part_0->SetupAttachment(BasePart);
	Part_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part_1"));
	Part_1->SetupAttachment(BasePart);
	Part_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part_2"));
	Part_2->SetupAttachment(BasePart);
	Part_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part_3"));
	Part_3->SetupAttachment(BasePart);
	
	Current.Add(Part_0, FRotator());
	Current.Add(Part_1, FRotator());
	Current.Add(Part_2, FRotator());
	Current.Add(Part_3, FRotator());

	Solution.Add(Part_0, FRotator(0.f, 0.f, 0.f));
	Solution.Add(Part_1, FRotator(0.f, 270.f, 0.f));
	Solution.Add(Part_2, FRotator(0.f, 180.f, 0.f));
	Solution.Add(Part_3, FRotator(0.f, -270.f, 0.f));
}

// Called when the game starts or when spawned
void AEyepieceStand::BeginPlay()
{
	Super::BeginPlay();
	
	Part_0->OnClicked.AddDynamic(this, &AEyepieceStand::RotatePart);
	Part_1->OnClicked.AddDynamic(this, &AEyepieceStand::RotatePart);
	Part_2->OnClicked.AddDynamic(this, &AEyepieceStand::RotatePart);
	Part_3->OnClicked.AddDynamic(this, &AEyepieceStand::RotatePart);

	Current.Add(Part_0, Part_0->GetRelativeRotation());
	Current.Add(Part_1, Part_1->GetRelativeRotation());
	Current.Add(Part_2, Part_2->GetRelativeRotation());
	Current.Add(Part_3, Part_3->GetRelativeRotation());
}

// Called every frame
void AEyepieceStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AEyepieceStand::IsSolved()
{
	for (auto Elem : Solution)
	{
		if (!Elem.Value.Equals(Current[Elem.Key]))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Orange, FString::Printf(TEXT("Rods.cpp - Solution: %s P: %f, Y: %f, R: %f"), *Elem.Key->GetName(), Elem.Value.Pitch, Elem.Value.Yaw, Elem.Value.Roll));
			//GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Orange, FString::Printf(TEXT("Rods.cpp - Current : %s P: %f, Y: %f, R: %f"), *Elem.Key->GetName(), Current[Elem.Key].Pitch, Current[Elem.Key].Yaw, Current[Elem.Key].Roll));
			return false;
		}
	}
	return true;
}

void AEyepieceStand::RotatePart(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	FRotator Rotation = Current[Cast<UStaticMeshComponent>(TouchedComponent)];
	Current.Add(Cast<UStaticMeshComponent>(TouchedComponent), Rotation.Add(-30.f, 0.f, 0.f));
	TouchedComponent->AddRelativeRotation(FRotator(-30.f, 0.f, 0.f), true);

	if (IsSolved())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("EyepieceStand.cpp - SOLVED")));
		OnSolve();
		bIsSolved = true;
	}

}
