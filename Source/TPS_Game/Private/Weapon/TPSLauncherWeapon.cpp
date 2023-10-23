// Third Person Shooter. All Rights Reserved.

#include "Weapon/TPSLauncherWeapon.h"
#include "Weapon/TPSProjectile.h"

void ATPSLauncherWeapon::StartFire()
{
    MakeShot();
}

void ATPSLauncherWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
        return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ATPSProjectile* Projectile = GetWorld()->SpawnActorDeferred<ATPSProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
}
