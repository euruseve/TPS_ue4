// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TPSWeaponComponent.h"
#include "TPSAIWeaponComponent.generated.h"

UCLASS()
class TPS_GAME_API UTPSAIWeaponComponent : public UTPSWeaponComponent
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
