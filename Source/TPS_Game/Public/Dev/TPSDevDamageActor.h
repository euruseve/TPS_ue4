
// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSDevDamageActor.generated.h"

UCLASS()
class TPS_GAME_API ATPSDevDamageActor : public AActor
{
    GENERATED_BODY()

public:
    ATPSDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Emerald;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) 
    float Damage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) 
    bool DoFullDamage = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) 
    TSubclassOf<UDamageType> DamageType;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
