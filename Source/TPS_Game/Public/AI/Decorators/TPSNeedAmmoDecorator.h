// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TPSNeedAmmoDecorator.generated.h"

class ATPSBaseWeapon;

UCLASS()
class TPS_GAME_API UTPSNeedAmmoDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    UTPSNeedAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ATPSBaseWeapon> WeaponType; 

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};