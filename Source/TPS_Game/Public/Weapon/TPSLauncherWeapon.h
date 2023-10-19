// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/TPSBaseWeapon.h"
#include "TPSLauncherWeapon.generated.h"

class ATPSProjectile;

UCLASS()
class TPS_GAME_API ATPSLauncherWeapon : public ATPSBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite)
    TSubclassOf<ATPSProjectile> ProjectileClass;

    virtual void MakeShot() override;
};
