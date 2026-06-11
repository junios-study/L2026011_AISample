// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckDistance.h"
#include "AIController.h"
#include "Zombie.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckDistance::UBTTask_CheckDistance()
{
	NodeName = TEXT("CheckDistance");
}

EBTNodeResult::Type UBTTask_CheckDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	AZombie* Zombie = Cast<AZombie>(OwnerComp.GetAIOwner()->GetPawn());

	if (Player && Zombie)
	{
		FVector ZombieLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		float Distance = FVector::Distance(ZombieLocation, PlayerLocation);

		if (ECondition::LessThen == TargetCondition)
		{
			if (TargetDistance > Distance)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)TargetState);
				Zombie->SetCurrentState(TargetState);
			}

		}
		else if (ECondition::GreaterThen == TargetCondition)
		{
			if (TargetDistance < Distance)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)TargetState);
				Zombie->SetCurrentState(TargetState);
			}
		}
	}

	

	return EBTNodeResult::Succeeded;
}
