// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TPSChangeWeaponService.generated.h"

UCLASS()
class TPS_GAME_API UTPSChangeWeaponService : public UBTService
{
    GENERATED_BODY()

public:
    UTPSChangeWeaponService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;


    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
