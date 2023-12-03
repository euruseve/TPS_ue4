// Third Person Shooter. All Rights Reserved. 

#include "UI/TPSSpectatorWidget.h"
#include "TPSUtils.h"
#include "Components/TPSRespawnComponent.h"

bool UTPSSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = TPSUtils::GetTPSPlayerComponent<UTPSRespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawningProgress())
        return false;

    CountDownTime = RespawnComponent->GetRespawnCountDown();
    return true;
}
