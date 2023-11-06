// Third Person Shooter. All Rights Reserved. 


#include "AI/Decorators/TPSNeedAmmoDecorator.h"
#include "Components/TPSWeaponComponent.h"
#include "AIController.h"
#include "TPSUtils.h"

UTPSNeedAmmoDecorator::UTPSNeedAmmoDecorator() 
{
    NodeName = "Need Ammo";
}

bool UTPSNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto WeaponComponent = TPSUtils::GetTPSPlayerComponent<UTPSWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
