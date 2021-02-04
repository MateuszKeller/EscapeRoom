// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "EyepieceStand.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API AEyepieceStand : public APuzzle
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEyepieceStand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool IsSolved_Implementation() override;

public:
	UFUNCTION()
	void RotatePart(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UStaticMeshComponent*, FRotator> Current;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UStaticMeshComponent*, FRotator> Solution;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* BasePart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Part_0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Part_1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Part_2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Part_3;
};
