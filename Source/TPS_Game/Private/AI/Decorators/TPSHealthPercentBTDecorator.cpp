// Third Person Shooter. All Rights Reserved.

#include "AI/Decorators/TPSHealthPercentBTDecorator.h"
#include "Components/TPSHealthComponent.h"
#include "AIController.h"
#include "TPSUtils.h"

UTPSHealthPercentBTDecorator::UTPSHealthPercentBTDecorator()
{
    NodeName = "Health Percent";
}

bool UTPSHealthPercentBTDecorator::CalculateRawConditionValue(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto HealthComponent = TPSUtils::GetTPSPlayerComponent<UTPSHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
