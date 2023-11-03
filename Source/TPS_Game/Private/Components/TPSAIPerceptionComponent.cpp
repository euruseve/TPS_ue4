// Third Person Shooter. All Rights Reserved.

#include "Components/TPSAIPerceptionComponent.h"
#include "TPSUtils.h"
#include "AIController.h"
#include "Components/TPSHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UTPSAIPerceptionComponent::GetClosesEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
        return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller)
        return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

    for (const auto PercieveActor : PercieveActors)
    {
        const auto HealthComponent = TPSUtils::GetTPSPlayerComponent<UTPSHealthComponent>(PercieveActor);

        // TODO: check if enemies or not
        if (HealthComponent && !HealthComponent->IsDead())
        {
            const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();

            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercieveActor;
            }
        }
    }

    return BestPawn;
}
