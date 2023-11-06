// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TPSHealthPercentBTDecorator.generated.h"

UCLASS()
class TPS_GAME_API UTPSHealthPercentBTDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    UTPSHealthPercentBTDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
