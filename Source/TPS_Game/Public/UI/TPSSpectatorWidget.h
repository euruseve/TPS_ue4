// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSSpectatorWidget.generated.h"

UCLASS()
class TPS_GAME_API UTPSSpectatorWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32& CountDownTime) const;
};
