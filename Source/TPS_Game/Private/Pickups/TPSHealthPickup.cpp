// Third Person Shooter. All Rights Reserved.

#include "Pickups/TPSHealthPickup.h"
#include "Components/TPSHealthComponent.h"
#include "TPSUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

 bool ATPSHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
     const auto HealthComponent = TPSUtils::GetTPSPlayerComponent<UTPSHealthComponent>(PlayerPawn);
     if (!HealthComponent)
         return false;

     return HealthComponent->TryToAddHealth(HealthAmount);
 }