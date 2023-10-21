// Third Person Shooter. All Rights Reserved.

#include "Components/TPSWeaponComponent.h"
#include "Weapon/TPSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/TPSEquipFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

UTPSWeaponComponent::UTPSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTPSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    InitAnimations();
    CurrentWeaponIndex = 0;
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UTPSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void UTPSWeaponComponent::SpawnWeapons()
{

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    for (auto WeaponClass : WeaponClasses)
    {
        auto Weapon = GetWorld()->SpawnActor<ATPSBaseWeapon>(WeaponClass);
        if (!Weapon)
            continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void UTPSWeaponComponent::AttachWeaponToSocket(
    ATPSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent)
        return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UTPSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UTPSWeaponComponent::StartFire()
{
    if (!CanFire())
        return;

    CurrentWeapon->StartFire();
}

void UTPSWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;

    CurrentWeapon->StopFire();
}

void UTPSWeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;

    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UTPSWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    Character->PlayAnimMontage(Animation);
}

void UTPSWeaponComponent::InitAnimations()
{
    if (!EquipAnimMontage)
        return;
    const auto NotifyEvents = EquipAnimMontage->Notifies;

    for (auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishNotify = Cast<UTPSEquipFinishedAnimNotify>(NotifyEvent.Notify);
        if (EquipFinishNotify)
        {
            EquipFinishNotify->OnNotified.AddUObject(this, &UTPSWeaponComponent::OnEquipFinished);
            break;
        }
    }
}

void UTPSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent)
        return;

    EquipAnimInProgress = false;
}

bool UTPSWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress;
}

bool UTPSWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}
