// Third Person Shooter. All Rights Reserved.

#include "Weapon/TPSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

ATPSBaseWeapon::ATPSBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ATPSBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}
