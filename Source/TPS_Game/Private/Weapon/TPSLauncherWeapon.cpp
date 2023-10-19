// Third Person Shooter. All Rights Reserved. 


#include "Weapon/TPSLauncherWeapon.h"
#include "Weapon/TPSProjectile.h"
#include "Kismet/GameplayStatics.h"

void ATPSLauncherWeapon::StartFire()
{
    MakeShot();
}

void ATPSLauncherWeapon::MakeShot() 
{
    const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);

    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
