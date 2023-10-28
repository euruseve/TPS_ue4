// Third Person Shooter. All Rights Reserved.

#include "Weapon/TPSProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/TPSWeaponFXComponent.h"

ATPSProjectile::ATPSProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.f;
    MovementComponent->ProjectileGravityScale = 0.1f;

    WeaponFXComponent = CreateDefaultSubobject<UTPSWeaponFXComponent>("WeaponFXComponent");
}

void ATPSProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ATPSProjectile::OnProjectileHit);
    CollisionComponent->bReturnMaterialOnMove = true;

    SetLifeSpan(LifeSeconds);
}

void ATPSProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld())
        return;

    MovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(GetWorld(), //
        DamageAmount,                               //
        GetActorLocation(),                         //
        DamageRadius,                               //
        UDamageType::StaticClass(),                 //
        {},                                         //
        this,                                       //
        GetController(),                            //
        DoFullDamage);

    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.f);

    WeaponFXComponent->PlayImpactFX(Hit);

    Destroy();  
}

AController* ATPSProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
