// Third Person Shooter. All Rights Reserved. 

#include "UI/TPSGameDataWidget.h"
#include "TPSGameModeBase.h"
#include "Player/TPSPlayerState.h"

int32 UTPSGameDataWidget::GetKillsNum() const
{
    const auto PlayerState = GetTPSPlayerState();
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UTPSGameDataWidget::GetDeathsNum() const
{
    const auto PlayerState = GetTPSPlayerState();
    return PlayerState ? PlayerState->GetDeathsNum() : 0;
}

int32 UTPSGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetTPSGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UTPSGameDataWidget::GetTotalRoundsNum() const
{
    const auto GameMode = GetTPSGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNums : 0;
}

int32 UTPSGameDataWidget::GetRoundSecondsRemaining() const
{
    const auto GameMode = GetTPSGameMode();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ATPSGameModeBase* UTPSGameDataWidget::GetTPSGameMode() const
{
    return GetWorld() ? Cast<ATPSGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ATPSPlayerState* UTPSGameDataWidget::GetTPSPlayerState() const
{
    return GetOwningPlayer() ? Cast<ATPSPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
