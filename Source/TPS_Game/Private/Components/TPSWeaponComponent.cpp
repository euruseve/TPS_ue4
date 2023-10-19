// Third Person Shooter. All Rights Reserved.

#include "Components/TPSWeaponComponent.h"
#include "Weapon/TPSBaseWeapon.h"
#include "GameFramework/Character.h"

UTPSWeaponComponent::UTPSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTPSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    SpawnWeapon();
}

void UTPSWeaponComponent::SpawnWeapon()
{
    if (!GetWorld())
        return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;
    
    CurrentWeapon = GetWorld()->SpawnActor<ATPSBaseWeapon>(WeaponClass);
    if (!CurrentWeapon)
        return;


    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
    CurrentWeapon->SetOwner(Character);
}

void UTPSWeaponComponent::StartFire() 
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->StartFire();
}

void UTPSWeaponComponent::StopFire() 
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->StopFire();
}