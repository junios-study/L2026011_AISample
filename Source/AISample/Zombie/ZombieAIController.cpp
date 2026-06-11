// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "Zombie.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "AISampleCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


AZombieAIController::AZombieAIController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	//Blueprint가 편함.
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConig"));
	SightConfig->SightRadius = 800.0f;
	SightConfig->LoseSightRadius = 900.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	//이기능 쓰려면 c++만 됨
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	
	Perception->ConfigureSense(*SightConfig);
	Perception->SetDominantSense(*SightConfig->GetSenseImplementation());

}

void AZombieAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AZombie* Zombie = Cast<AZombie>(InPawn);
	if (Zombie)
	{
		RunBehaviorTree(Zombie->RunBTAsset);
	}

	SetGenericTeamId(3);
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AZombieAIController::ProcessPerception);
	Perception->OnTargetPerceptionForgotten.AddDynamic(this, &AZombieAIController::ProcessPerceptinoForgotten);

}

void AZombieAIController::ProcessPerception(AActor* Actor, FAIStimulus Stimulus)
{


	if (UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) == UAISense_Hearing::StaticClass())
	{
		UE_LOG(LogTemp, Warning, TEXT("I Hear You."));
	}

	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		AZombie* Zombie = Cast<AZombie>(GetPawn());
		AAISampleCharacter* Player = Cast<AAISampleCharacter>(Actor);
		if (!Zombie || !Player)
		{
			return;
		}

		if (Zombie->CurrentState == EZombieState::Death)
		{
			return;
		}

		if (Stimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("Zombie is chase."));
			Zombie->SetCurrentState(EZombieState::Chase);
			Blackboard->SetValueAsEnum("CurrentState", (uint8)EZombieState::Chase);
			Blackboard->SetValueAsObject(TEXT("Player"), Player);
		}
		else
		{
			Zombie->SetCurrentState(EZombieState::Normal);
			Blackboard->SetValueAsEnum("CurrentState", (uint8)EZombieState::Normal);
		}
	}
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			UE_LOG(LogTemp, Warning, TEXT("I Hear You."));
			//Stimulus.Tag.IsEqual("Person");
		}
	}
}

void AZombieAIController::ProcessPerceptinoForgotten(AActor* Actor)
{
}
