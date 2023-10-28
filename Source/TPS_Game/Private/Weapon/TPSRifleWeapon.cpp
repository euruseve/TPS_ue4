// Third Person Shooter. All Rights Reserved. 


#include "Weapon/TPSRifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/TPSWeaponFXComponent.h"

ATPSRifleWeapon::ATPSRifleWeapon() 
{
    WeaponFXComponent = CreateDefaultSubobject<UTPSWeaponFXComponent>("WeaponFXComponent");
}

void ATPSRifleWeapon::BeginPlay() 
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}


void ATPSRifleWeapon::StartFire()
{
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ATPSRifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void ATPSRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}


void ATPSRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        //DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Orange, false, 3.f, 0, 3.f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Orange, false, 3.f, 0, 3.f);
    }


    DecreaseAmmo();
}

bool ATPSRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;

    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ATPSRifleWeapon::MakeDamage(FHitResult& HitResult)
{
    const auto DamageActor = HitResult.GetActor();

    if (!DamageActor)
        return;

    DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}