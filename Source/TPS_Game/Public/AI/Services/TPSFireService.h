// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TPSFireService.generated.h"

UCLASS()
class TPS_GAME_API UTPSFireService : public UBTService
{
    GENERATED_BODY()

public:
    UTPSFireService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
