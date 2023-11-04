// Third Person Shooter. All Rights Reserved.

#include "AI/Services/TPSFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/TPSAIPerceptionComponent.h"
#include "Components/TPSWeaponComponent.h"
#include "AIController.h"
#include "TPSUtils.h"

UTPSFireService::UTPSFireService() 
{
    NodeName = "Fire";
}

void UTPSFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
  
    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = TPSUtils::GetTPSPlayerComponent<UTPSWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
