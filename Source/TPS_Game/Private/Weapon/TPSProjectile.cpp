// Third Person Shooter. All Rights Reserved.

#include "Weapon/TPSProjectile.h"
#include "Components/SphereComponent.h"

ATPSProjectile::ATPSProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.f);
    SetRootComponent(CollisionComponent);
}

void ATPSProjectile::BeginPlay()
{
    Super::BeginPlay();

}
