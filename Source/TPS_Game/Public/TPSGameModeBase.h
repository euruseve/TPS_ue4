// Third Person Shooter. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSCoreTypes.h"
#include "TPSGameModeBase.generated.h"

class AAIController;

UCLASS()
class TPS_GAME_API ATPSGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATPSGameModeBase();

    virtual void StartPlay() override;

    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void Killed(AController* KillerController, AController* VictimController);

    FGameData GetGameData() { return GameData; }
    int32 GetCurrentRoundNum() { return CurrentRound; }
    int32 GetRoundSecondsRemaining() { return RoundCountDown; }

    void RespawnRequest(AController* Controller);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

private:
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamId(int TeamId) const;
    void SetPlayerColor(AController* Controller);

    void LogPlayerInfo();

    void StartRespawn(AController* Controller);
};
