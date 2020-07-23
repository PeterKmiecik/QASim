#include "Tank.h"
#include "BattleTank.h"

#include "Math/Rotator.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/InputComponent.h"
#include "Components/AudioComponent.h"

#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankTurret.h"
#include "TankTrack.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(TEXT("TankAimingComponent"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(TEXT("TankMovementComponent"));
	AddOwnedComponent(TankMovementComponent);
	AddOwnedComponent(TankAimingComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!ensure(PlayerInputComponent)) {UE_LOG(XXXXX_Log_BT, Error, TEXT("[BT][%s] NoPlayerInputComponent"), *this->GetName()); return;}

	PlayerInputComponent->BindAxis("MouseX", this, &ATank::Turn);
	PlayerInputComponent->BindAxis("MouseY", this, &ATank::LookUp);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void ATank::Init()
{
	CurrentHealth = StartingHealth;
	if (EngineSound)
	{
		SetupEngineSounds(EngineSound);
	} else { UE_LOG(XXXXX_Log_BT, Warning, TEXT("@@@@@ [%s] has no EngineSound set in BPs defaults"), *this->GetName()); }
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

void ATank::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void ATank::Turn(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return DamageToApply;
}

void ATank::StabilizeTurretYaw(float Throw) {

	// // Zeroing Turret rotation casued by tank rotation
	auto Turret = TankAimingComponent->GetTurret();
	if (!ensure(Turret)) { UE_LOG(XXXXX_Log_BT, Warning, TEXT("[BT] [%s] TankAimingComponent has no Turret assigned !"), *this->GetName()); return;}
	if (Throw != 0)
	{
		float CurrentTurretRotation = Turret->GetComponentRotation().Yaw;
		float TankRotation = this->GetActorRotation().Yaw;
		float DeltaTankRotation = TankRotationBeforeInput.Yaw - TankRotation;
			//UE_LOG(XXXXX_Log_BT, Warning, TEXT("[%s] Relative toation: [%f]"), *this->GetName(), CurrentRotation.Yaw);
	
		DeltaTankRotation =  FMath::ClampAngle(DeltaTankRotation, -0.5f, 0.5f);
		FRotator Delta = FRotator(0.f, DeltaTankRotation, 0.f);
		Turret->bAbsoluteRotation = true;
		Turret->AddRelativeRotation(Delta.GetNormalized());
		//UE_LOG(XXXXX_Log_BT, Warning, TEXT("[BT] [%s] DeltaTankRotation is [%f]  and turret COMPONENT [%f] "), *this->GetName(), DeltaTankRotation, CurrentTurretRotation);
		
	}
	else {
	TankRotationBeforeInput = GetActorRotation();
	}
	//UE_LOG(XXXXX_Log_BT, Warning, TEXT("[BT] [%] FPlatformTime::Seconds() [%f]"), *this->GetName(), FPlatformTime::Seconds());
}

void ATank::SetupEngineSounds(USoundBase* Sound)
{
	if (Sound)
	{
		TankEngineAudioComp = UGameplayStatics::SpawnSoundAttached(Sound, GetRootComponent(), NAME_None, GetActorLocation(), EAttachLocation::SnapToTarget, true, 1.f, 1.f, 0.f);
	}
}

void ATank::EnginePitchHandler()
{
	float NewPitch;
	UTankTrack* LeftTrack = TankMovementComponent->GetLeftTrack();
	UTankTrack* RightTrack = TankMovementComponent->GetRightTrack();

	float IncomingDrivingDirection = LeftTrack->GetPositionOffset(LeftTrack->GetCurrentThrottle());
	//UE_LOG(XXXXX_Log_BT, Log, TEXT("[BT] [%s] TrackOffset [%f] !"), *this->GetName(), LeftTrack->GetPositionOffset(LeftTrack->GetCurrentThrottle()));

	// if we are turning
	if ((LeftTrack->GetCurrentThrottle() > 0.f) && (RightTrack->GetCurrentThrottle() < 0.f))
	{
		// make pitch of engine at low level
		NewPitch = UKismetMathLibrary::MapRangeClamped(IncomingDrivingDirection, -0.002f, 0.002f, LowEnginePitch, LowEnginePitch);
	}
	else
	{
		NewPitch = UKismetMathLibrary::MapRangeClamped(IncomingDrivingDirection, -0.002f, 0.002f, LowEnginePitch, HighEnginePitch);
	}
	//UE_LOG(XXXXX_Log_BT, Log, TEXT("[BT] [%s] SoundPitchMultipier [%f] !"), *this->GetName(), NewPitch)
	TankEngineAudioComp->SetPitchMultiplier(NewPitch);
}


