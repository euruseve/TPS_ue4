// Third Person Shooter. All Rights Reserved.

#include "TPSGameModeBase.h"

#include "Player/TPSBaseCharacter.h"
#include "Player/TPSPlayerController.h"
#include "UI/TPSGameHUD.h"


ATPSGameModeBase::ATPSGameModeBase()
{
    DefaultPawnClass = ATPSBaseCharacter::StaticClass();
    PlayerControllerClass = ATPSPlayerController::StaticClass();
    HUDClass = ATPSGameHUD::StaticClass();
}
