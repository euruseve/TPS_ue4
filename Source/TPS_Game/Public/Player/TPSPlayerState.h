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

private:
    int32 TeamId;
    FLinearColor TeamColor;
};
