// Third Person Shooter. All Rights Reserved.

#include "Animations/TPSEquipFinishedAnimNotify.h"

void UTPSEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);

    Super::Notify(MeshComp, Animation);
}
