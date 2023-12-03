// Third Person Shooter. All Rights Reserved.

#include "TPSGameModeBase.h"
#include "AIController.h"
#include "Player/TPSBaseCharacter.h"
#include "Player/TPSPlayerController.h"
#include "UI/TPSGameHUD.h"
#include "TPSUtils.h"
#include "Player/TPSPlayerState.h"
#include "Components/TPSRespawnComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

ATPSGameModeBase::ATPSGameModeBase()
{
    DefaultPawnClass = ATPSBaseCharacter::StaticClass();
    PlayerControllerClass = ATPSPlayerController::StaticClass();
    HUDClass = ATPSGameHUD::StaticClass();
    PlayerStateClass = ATPSPlayerState::StaticClass();
}

void ATPSGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();

    CurrentRound = 1;
    StartRound();
}

UClass* ATPSGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ATPSGameModeBase::SpawnBots()
{
    if (!GetWorld())
        return;

    for (int32 i = 0; i < GameData.PlayerNums - 1; i++)
    {
        FActorSpawnParameters SpawnInfo;

        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto TPSAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(TPSAIController);
    }
}

void ATPSGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundsTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ATPSGameModeBase::GameTimerUpdate, 1.f, true);
}

void ATPSGameModeBase::GameTimerUpdate()
{
    UE_LOG(
        LogGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNums);

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNums)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            UE_LOG(LogGameModeBase, Display, TEXT("########## GAME OVER ##########"));
            LogPlayerInfo();
        }
    }
}

void ATPSGameModeBase::ResetPlayers()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; It++)
    {
        ResetOnePlayer(It->Get());
    }
}

void ATPSGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
        Controller->GetPawn()->Reset();

    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ATPSGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld())
        return;

    int32 TeamId = 1;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ATPSPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->SetTeamId(TeamId);
        PlayerState->SetTeamColor(DetermineColorByTeamId(TeamId));

        SetPlayerColor(Controller);
        // UE_LOG(LogGameModeBase, Warning, TEXT("Team id have been seted: %i"), TeamId);

        TeamId = TeamId == 1 ? 2 : 1;
    }
}

FLinearColor ATPSGameModeBase::DetermineColorByTeamId(int TeamId) const
{
    if (TeamId - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamId - 1];
    }
    UE_LOG(LogGameModeBase, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamId,
        *GameData.DefaultTeamColor.ToString());
    return GameData.DefaultTeamColor;
}

void ATPSGameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller)
        return;

    const auto Character = Cast<ATPSBaseCharacter>(Controller->GetPawn());
    if (!Character)
        return;

    const auto PlayerState = Cast<ATPSPlayerState>(Controller->PlayerState);
    if (!PlayerState)
        return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ATPSGameModeBase::LogPlayerInfo()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ATPSPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->LogInfo();
    }
}

void ATPSGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    const auto KillerPlayerState = KillerController ? Cast<ATPSPlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<ATPSPlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }

    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void ATPSGameModeBase::StartRespawn(AController* Controller)
{
    const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
    if (!RespawnAvailable)
        return;


    const auto RespawnComponent = TPSUtils::GetTPSPlayerComponent<UTPSRespawnComponent>(Controller);
    if (!RespawnComponent)
        return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ATPSGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}
