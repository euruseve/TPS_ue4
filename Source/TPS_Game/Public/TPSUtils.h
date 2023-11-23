#pragma once
#include "Player/TPSPlayerState.h"

class TPSUtils
{
public:
    template <typename T> static T* GetTPSPlayerComponent(AActor* PlayerPawn)
    {
        if (!PlayerPawn)
            return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());

        return Cast<T>(Component);
    }

    bool static AreEnemies(AController* Controller1, AController* Controller2)
    {
        if (!Controller1 || !Controller2 || Controller1 == Controller2)
            return false;

        const auto PlayerState1 = Cast<ATPSPlayerState>(Controller1);
        const auto PlayerState2 = Cast<ATPSPlayerState>(Controller2);

        return PlayerState1 && PlayerState2 && (PlayerState1->GetTeamId() != PlayerState2->GetTeamId());
    }
};