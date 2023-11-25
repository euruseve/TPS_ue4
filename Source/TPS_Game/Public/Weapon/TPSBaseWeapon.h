// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSCoreTypes.h"
#include "TPSBaseWeapon.generated.h"


class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;


UCLASS()
class TPS_GAME_API ATPSBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ATPSBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

    virtual void StartFire();
    virtual void StopFire();
    void ChangeClip();
    bool CanReload() const;

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetAmmoData() const { return CurrentAmmo; }

    bool TryToAddAmmo(int32 ClipsAmount);
    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* MuzzleFX;

    virtual void BeginPlay() override;

    virtual void MakeShot();

    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    bool GetPlayerViewPoint(FVector& ViewLocaion, FRotator& ViewRotation) const;

    FVector GetMuzzleWorldLocation() const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

    void DecreaseAmmo();
    
    bool IsClipEmpty() const;
    
    
    void LogAmmo();

    UNiagaraComponent* SpawnMuzzleFX();

private:
    FAmmoData CurrentAmmo;
};