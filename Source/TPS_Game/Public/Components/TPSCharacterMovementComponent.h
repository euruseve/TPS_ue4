// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPSCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class TPS_GAME_API UTPSCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "5"))
    float RunModifier = 2.f;

    virtual float GetMaxSpeed() const override;
};
