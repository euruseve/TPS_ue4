// Third Person Shooter. All Rights Reserved.
#include "Player/TPSPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPSPlayerState, All, All);


void ATPSPlayerState::LogInfo() 
{
    UE_LOG(LogTPSPlayerState, Display, TEXT("TeamId: %i | Kills: %i | Deaths: %i"), TeamId, KillsNum, DeathsNum);
}
	