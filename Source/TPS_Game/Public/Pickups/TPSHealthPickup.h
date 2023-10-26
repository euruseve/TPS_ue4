// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/TPSBasePickup.h"
#include "TPSHealthPickup.generated.h"

UCLASS()
class TPS_GAME_API ATPSHealthPickup : public ATPSBasePickup
{
    GENERATED_BODY()

    protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    float HealthAmount = 100.f;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
