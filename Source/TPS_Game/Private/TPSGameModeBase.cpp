// Third Person Shooter. All Rights Reserved.

#include "TPSGameModeBase.h"

void ATPSGameModeBase::TestF()
{
    int32 Var = 0;
    if (Var < 30)
    {
        for (int32 i = 0; i < 10; i++)
        {
            UE_LOG(LogTemp, Warning, TEXT("Err"));
        }
    }
}