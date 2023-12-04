// Third Person Shooter. All Rights Reserved. 


#include "Player/TPSPlayerController.h"
#include "Components/TPSRespawnComponent.h"

ATPSPlayerController::ATPSPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UTPSRespawnComponent>("RespawnComponent");
}

void ATPSPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}
