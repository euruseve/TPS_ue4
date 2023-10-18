// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class TPS_GAME_API ATPSBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ATPSBaseWeapon();

    virtual void Fire();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.f;

    void MakeShot();

    APlayerController* GetPlayerController() const;

    bool GetPlayerViewPoint(FVector& ViewLocaion, FRotator& ViewRotation) const;

    FVector GetMuzzleWorldLocation() const;

    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

    virtual void BeginPlay() override;
};