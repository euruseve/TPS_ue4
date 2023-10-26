// Third Person Shooter. All Rights Reserved.

#include "Pickups/TPSAmmoPickup.h"
#include "Components/TPSHealthComponent.h"
#include "Components/TPSWeaponComponent.h"
#include "TPSUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ATPSAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = TPSUtils::GetTPSPlayerComponent<UTPSHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    const auto WeaponComponent = TPSUtils::GetTPSPlayerComponent<UTPSWeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
        return false;
        

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
