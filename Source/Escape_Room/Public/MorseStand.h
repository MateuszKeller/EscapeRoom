// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "MorseStand.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API AMorseStand : public APuzzle
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMorseStand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool IsSolved_Implementation() override;

	virtual void ShowOutline(bool Yes) override;

public:
	UFUNCTION()
	void SendLetter(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void Reset();
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void OnLookAt_Implementation(APlayerCharacter* Player) override;

	UPROPERTY(BlueprintReadWrite)
	bool bHasStoppedPlaying = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UStaticMeshComponent*, FString> Letters;

	FString Word;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Solution = "HASTUR";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Speaker;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Cylinder_Up;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Cylinder_Down;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Horn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Needle;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Button_0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Button_1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Button_2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Button_3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Button_4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Button_5;
};
