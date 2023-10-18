// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TPSGameHUD.generated.h"

/**
 *
 */
UCLASS()
class TPS_GAME_API ATPSGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

    private:
    void DrawCrossHair();
};
