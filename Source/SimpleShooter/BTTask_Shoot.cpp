
#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!PlayerPawn)
	{
		return EBTNodeResult::Failed;
	}

	auto Dist = FVector::Dist(PlayerPawn->GetActorLocation(), OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());
	//UE_LOG(LogTemp, Error, TEXT("DIST: %f"), Dist);

	if (Dist > 600)
	{
		return EBTNodeResult::Failed;
	}

	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character)
	{
		return EBTNodeResult::Failed;
	}

	Character->Shoot();

	return EBTNodeResult::Succeeded;
}
