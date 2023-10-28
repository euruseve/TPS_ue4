// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSCoreTypes.h"
#include "TPSWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TPS_GAME_API UTPSWeaponFXComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTPSWeaponFXComponent();

    void PlayImpactFX(const FHitResult& Hit);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FImpactData DefaultImpactData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
