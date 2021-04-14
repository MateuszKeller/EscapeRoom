// Fill out your copyright notice in the Description page of Project Settings.


#include "MorseStand.h"
#include "Others.h"
#include "PlayerCharacter.h"

// Sets default values
AMorseStand::AMorseStand()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	PuzzleMesh->SetupAttachment(Root);

	Horn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Horn"));
	Horn->SetupAttachment(Root);
	Horn->SetCustomDepthStencilValue(2);

	Cylinder_Up = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder_Up"));
	Cylinder_Up->SetupAttachment(Horn);
	Cylinder_Up->SetCustomDepthStencilValue(2);

	Cylinder_Down = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder_Down"));
	Cylinder_Down->SetupAttachment(Horn);
	Cylinder_Down->SetCustomDepthStencilValue(2);

	Needle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Needle"));
	Needle->SetupAttachment(Cylinder_Down);
	Needle->SetCustomDepthStencilValue(2);

	Speaker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Speaker"));
	Speaker->SetupAttachment(Horn);
	Speaker->SetCustomDepthStencilValue(2);

	Button_0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_0"));
	Button_0->SetupAttachment(Handle);
	Button_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_1"));
	Button_1->SetupAttachment(Handle);
	Button_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_2"));
	Button_2->SetupAttachment(Handle);
	Button_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_3"));
	Button_3->SetupAttachment(Handle);
	Button_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_4"));
	Button_4->SetupAttachment(Handle);
	Button_5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_5"));
	Button_5->SetupAttachment(Handle);

	Letters.Empty();
	Letters.Add(Button_0, "A");
	Letters.Add(Button_1, "H");
	Letters.Add(Button_2, "R");
	Letters.Add(Button_3, "S");
	Letters.Add(Button_4, "T");
	Letters.Add(Button_5, "U");
}

// Called when the game starts or when spawned
void AMorseStand::BeginPlay()
{
	Super::BeginPlay();

	Button_0->OnClicked.AddDynamic(this, &AMorseStand::SendLetter);
	Button_0->OnBeginCursorOver.AddDynamic(this, &AMorseStand::OnStartHover);
	Button_0->OnEndCursorOver.AddDynamic(this, &AMorseStand::OnEndHover);

	Button_1->OnClicked.AddDynamic(this, &AMorseStand::SendLetter);
	Button_1->OnBeginCursorOver.AddDynamic(this, &AMorseStand::OnStartHover);
	Button_1->OnEndCursorOver.AddDynamic(this, &AMorseStand::OnEndHover);

	Button_2->OnClicked.AddDynamic(this, &AMorseStand::SendLetter);
	Button_2->OnBeginCursorOver.AddDynamic(this, &AMorseStand::OnStartHover);
	Button_2->OnEndCursorOver.AddDynamic(this, &AMorseStand::OnEndHover);

	Button_3->OnClicked.AddDynamic(this, &AMorseStand::SendLetter);
	Button_3->OnBeginCursorOver.AddDynamic(this, &AMorseStand::OnStartHover);
	Button_3->OnEndCursorOver.AddDynamic(this, &AMorseStand::OnEndHover);

	Button_4->OnClicked.AddDynamic(this, &AMorseStand::SendLetter);
	Button_4->OnBeginCursorOver.AddDynamic(this, &AMorseStand::OnStartHover);
	Button_4->OnEndCursorOver.AddDynamic(this, &AMorseStand::OnEndHover);

	Button_5->OnClicked.AddDynamic(this, &AMorseStand::SendLetter);
	Button_5->OnBeginCursorOver.AddDynamic(this, &AMorseStand::OnStartHover);
	Button_5->OnEndCursorOver.AddDynamic(this, &AMorseStand::OnEndHover);

}

// Called every frame
void AMorseStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AMorseStand::IsSolved_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("MorseStand.cpp - Word:%s"), *Word));
	if (Word == Solution)
	{
		return true;
	}

	return false;
}

void AMorseStand::SendLetter(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player->State == EPlayerCharacterState::Puzzle)
	{
		if (FMath::IsNearlyEqual(TouchedComponent->GetRelativeLocation().X, 0.f, 0.01f))
		{
			FString l = Letters[Cast<UStaticMeshComponent>(TouchedComponent)];
			TouchedComponent->AddRelativeLocation(FVector(2.8f, 0.f, 0.f));
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("MorseStand.cpp - %f %s"), TouchedComponent->GetRelativeLocation().X, *l));
			Word.Append(Letters[Cast<UStaticMeshComponent>(TouchedComponent)]);

			if (IsSolved())
			{
				OnSolve();
				bIsSolved = true;
				//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("MorseStand.cpp.cpp - Solved")));
			}
			else
			{
				if (Word.Len() == 6)
				{
					Reset();
				}
			}
		}
	}
}

void AMorseStand::Reset()
{
	for (auto Elem : Letters)
	{
		Elem.Key->AddRelativeLocation(FVector(-2.8f, 0.f, 0.f));
	}
	Word = "";
}

void AMorseStand::OnLookAt_Implementation(APlayerCharacter* Player)
{
	if (!bIsSolved && bHasStoppedPlaying)
	{

		Player->OnPointerTextUpdate.Broadcast(Message);
		ShowOutline(true);

	}
}

void AMorseStand::ShowOutline(bool Yes)
{
	PuzzleMesh->SetRenderCustomDepth(Yes);
	Horn->SetRenderCustomDepth(Yes);
	Cylinder_Up->SetRenderCustomDepth(Yes);
	Cylinder_Down->SetRenderCustomDepth(Yes);
	Needle->SetRenderCustomDepth(Yes);
	Speaker->SetRenderCustomDepth(Yes);
}
