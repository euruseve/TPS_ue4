// Third Person Shooter. All Rights Reserved.

#include "Pickups/TPSBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ATPSBasePickup::ATPSBasePickup()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ATPSBasePickup::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);

    GenerateRotationYaw();
}

void ATPSBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) 
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

void ATPSBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.f, RotationYaw, 0.f));
}

bool ATPSBasePickup::CouldBeTaken() const
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

bool ATPSBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ATPSBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }


    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ATPSBasePickup::Respawn, RespawnTime);
}

void ATPSBasePickup::Respawn() 
{
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

void ATPSBasePickup::GenerateRotationYaw() 
{
    const auto Direction = FMath::RandBool() ? 1.f : -1.f;
    RotationYaw = FMath::RandRange(1.f, 2.f) * Direction;
}
