// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSPlayerController.generated.h"

class UTPSRespawnComponent;

UCLASS()
class TPS_GAME_API ATPSPlayerController : public APlayerController
{
    GENERATED_BODY()

    public:
    ATPSPlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTPSRespawnComponent* RespawnComponent;
};
