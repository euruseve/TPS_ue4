// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSRespawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TPS_GAME_API UTPSRespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTPSRespawnComponent();

    void Respawn(int32 RespawnTime);

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown = 0;

    void RespawnTimerUpdate();
};
