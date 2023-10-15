// Third Person Shooter. All Rights Reserved.

#include "Player/TPSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/TPSCharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATPSBaseCharacter::ATPSBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(
          ObjInit.SetDefaultSubobjectClass<UTPSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATPSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ATPSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATPSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ATPSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ATPSBaseCharacter::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &ATPSBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ATPSBaseCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPSBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ATPSBaseCharacter::OnStartRunnig);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ATPSBaseCharacter::OnStopRunnig);
}

bool ATPSBaseCharacter::IsRunning() const
{
    return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
}

float ATPSBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.f;

    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ATPSBaseCharacter::MoveForward(float Amount)
{
    bIsMovingForward = Amount > 0.f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ATPSBaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0.f)
        return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ATPSBaseCharacter::OnStartRunnig()
{
    bWantsToRun = true;
}

void ATPSBaseCharacter::OnStopRunnig()
{
    bWantsToRun = false;
}
