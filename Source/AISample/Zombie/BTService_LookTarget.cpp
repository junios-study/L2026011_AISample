// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LookTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_LookTarget::UBTService_LookTarget()
{
	NodeName = TEXT("LookTarget");
}

void UBTService_LookTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	AActor* Zombie = Cast<AActor>(OwnerComp.GetAIOwner()->GetPawn());

	if (Target && Zombie)
	{
		FVector TargetLocation = Target->GetActorLocation();
		FVector ZombieLocation = Zombie->GetActorLocation();

		FRotator LookRotator = UKismetMathLibrary::FindLookAtRotation(ZombieLocation, TargetLocation);

		FRotator TargetRotation = FMath::RInterpTo(Zombie->GetActorRotation(), LookRotator, DeltaSeconds, 10.0f);

		Zombie->SetActorRotation(LookRotator);
	}

}
