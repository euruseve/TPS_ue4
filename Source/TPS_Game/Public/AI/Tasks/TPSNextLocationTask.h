// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TPSNextLocationTask.generated.h"

UCLASS()
class TPS_GAME_API UTPSNextLocationTask : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UTPSNextLocationTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Radius = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimLocationKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool SelfCenter = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"))
    FBlackboardKeySelector CenterActorKey;
};