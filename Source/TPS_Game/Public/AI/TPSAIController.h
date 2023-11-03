// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TPSAIController.generated.h"

class UTPSAIPerceptionComponent;

UCLASS()
class TPS_GAME_API ATPSAIController : public AAIController
{
    GENERATED_BODY()

public:
    ATPSAIController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTPSAIPerceptionComponent* TPSAIPerceptionComponent;

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;
};
