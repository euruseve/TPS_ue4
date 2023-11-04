// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TPSFindEnemyService.generated.h"

UCLASS()
class TPS_GAME_API UTPSFindEnemyService : public UBTService
{
    GENERATED_BODY()

public:
    UTPSFindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
