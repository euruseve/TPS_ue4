// Third Person Shooter. All Rights Reserved.

#include "Components/TPSAIWeaponComponent.h"
#include "Weapon/TPSBaseWeapon.h"

void UTPSAIWeaponComponent::StartFire()
{
    if (!CanFire())
        return;

    if (CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void UTPSAIWeaponComponent::NextWeapon()
{
    if (!CanFire())
        return;

    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

    while (NextIndex != CurrentWeaponIndex)
    {
        if (!Weapons[NextIndex]->IsAmmoEmpty())
            break;

        NextIndex = (NextIndex + 1) % Weapons.Num();
    }

    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}
