// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSProjectile.generated.h"


class USphereComponent;

UCLASS()
class TPS_GAME_API ATPSProjectile : public AActor
{
    GENERATED_BODY()

public:
    ATPSProjectile();

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

    virtual void BeginPlay() override;
};
