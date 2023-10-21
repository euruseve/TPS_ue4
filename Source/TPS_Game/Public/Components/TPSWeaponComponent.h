// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSWeaponComponent.generated.h"

class ATPSBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TPS_GAME_API UTPSWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTPSWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ATPSBaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    ATPSBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ATPSBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;
    bool EquipAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(ATPSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void EquipWeapon(int32 WeaponIndex);
    void PlayAnimMontage(UAnimMontage* Animation);

    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

    bool CanFire() const;
    bool CanEquip() const;
};
