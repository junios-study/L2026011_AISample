// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "Zombie.h"

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AZombie* Zombie = Cast<AZombie>(InPawn);
	if (Zombie)
	{
		RunBehaviorTree(Zombie->RunBTAsset);
	}
}
