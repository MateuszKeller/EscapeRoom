// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePart.generated.h"

//Delegate to tell Puzzle that this part is solved
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSolve);

UCLASS(ABSTRACT)
class ESCAPE_ROOM_API APuzzlePart : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzlePart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Puzzle Part")
	void Solve();
	virtual void Solve_Implementation();

	UFUNCTION()
	void OnClickedTake(AActor* TouchedActor, FKey ButtonPressed);

	UFUNCTION()
	void OnStartHover(AActor* TouchedActor);

	UFUNCTION()
	void OnEndHover(AActor* TouchedActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle Part")
	UStaticMeshComponent* PPMeshComponent;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnSolve OnSolve;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Puzzle Part")
	bool bIsSolved = false;
};
