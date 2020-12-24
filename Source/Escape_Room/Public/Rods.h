// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "Math/Color.h"
#include "Rods.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API ARods : public APuzzle
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARods();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    virtual bool IsSolved() override;

public:

    UFUNCTION(BlueprintImplementableEvent)
    void ChangeMaterial(UStaticMeshComponent* Rod, FColor Color);

    UFUNCTION()
    void ChangeColor(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TArray<FColor> Colors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<UStaticMeshComponent*, int32> Current;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<UStaticMeshComponent*, int32> Solution;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Rod_0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Rod_1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Rod_2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Rod_3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* Rod_4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APuzzleAnswerer* Answerer;

};

/*class Rods: Puzzle
{
    TArray<FColor> Colors = [FColor:White];
    TMap<UStaticMeshComponent, int> Current;

    TMap<UStaticMeshComponent, int> Solution;

    UFUNCTION(BlueprintNative)
    void ChangeMaterial(UStaticMeshComponent Rod, FColor Color);

    void ChangeColor(Actor Touched)
    {
        int ColorNumber = Current[Touched];
        Current.Add(Touched, ColorNumber++);
        ChangeMaterial(Touched, Colors[ColorNumber]);
        if(IsSolved)
            Solve();

    }
    
    bool IsSolved()
    {
        for(auto& Elem: Solution)
        {
            if(Elem.Value != Current[Elem.Key].Value)
                return false;
        }
        
        return true;
    }

               

}*/