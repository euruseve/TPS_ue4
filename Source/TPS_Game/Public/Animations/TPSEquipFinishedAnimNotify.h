// Third Person Shooter. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TPSEquipFinishedAnimNotify.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);


UCLASS()
class TPS_GAME_API UTPSEquipFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FOnNotifiedSignature OnNotified;
};
