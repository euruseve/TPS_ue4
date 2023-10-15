// Third Person Shooter. All Rights Reserved.

#include "TPSGameModeBase.h"

#include "Player/TPSBaseCharacter.h"
#include "Player/TPSPlayerController.h"


ATPSGameModeBase::ATPSGameModeBase()
{
    DefaultPawnClass = ATPSBaseCharacter::StaticClass();
    PlayerControllerClass = ATPSPlayerController::StaticClass();
}
