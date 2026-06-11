// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class AISAMPLE_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:

	AZombieAIController();

	virtual void OnPossess(APawn* InPawn) override;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> Perception;

	UFUNCTION()
	void ProcessPerception(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void ProcessPerceptinoForgotten(AActor* Actor);

};
