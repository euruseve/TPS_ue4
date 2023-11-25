// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/TPSBaseWeapon.h"
#include "TPSRifleWeapon.generated.h"

class UTPSWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class TPS_GAME_API ATPSRifleWeapon : public ATPSBaseWeapon
{
    GENERATED_BODY()

public:
    ATPSRifleWeapon();
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UTPSWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";


    virtual void BeginPlay() override;
    
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    void MakeDamage(FHitResult& HitResult);

    void InitMuzzleFX();
    void SetMuzzleFXVisibility(bool Visible);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
    AController* GetController() const;
};
