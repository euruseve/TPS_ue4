// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPSPlayerState.generated.h"

UCLASS()
class TPS_GAME_API ATPSPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    void SetTeamId(int32 Id) { TeamId = Id; }
    int32 GetTeamId() const { return TeamId; }

    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
    FLinearColor GetTeamColor() const { return TeamColor; }

    void AddKill() { ++KillsNum; }
    int32 GetKillsNum() const { return KillsNum; }

    void AddDeath() { ++DeathsNum; }
    int32 GetDeathsNum() const { return DeathsNum; }

    void LogInfo();

private:
    int32 TeamId;
    FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathsNum = 0;
};
