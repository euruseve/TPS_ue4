// Third Person Shooter. All Rights Reserved.

#include "Weapon/Components/TPSWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

UTPSWeaponFXComponent::UTPSWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTPSWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
    auto ImpactData = DefaultImpactData;    


    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    // NIAGARA
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(), ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

    // DECAL
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), //
        ImpactData.DecalData.Material,                 //
        ImpactData.DecalData.Size,                     //
        Hit.ImpactPoint,                               //
        Hit.ImpactNormal.Rotation());

    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }
}
