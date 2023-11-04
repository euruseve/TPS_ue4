// Third Person Shooter. All Rights Reserved.

#include "AI/Services/TPSFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/TPSAIPerceptionComponent.h"
#include "AIController.h"
#include "TPSUtils.h"

UTPSFindEnemyService::UTPSFindEnemyService()
{
    NodeName = "Find Enemy";
}

void UTPSFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    // UE_LOG(LogTemp, Display, TEXT("Find enemy"));
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = TPSUtils::GetTPSPlayerComponent<UTPSAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosesEnemy());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
