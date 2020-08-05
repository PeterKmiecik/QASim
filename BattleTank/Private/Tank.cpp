#include "Tank.h"
#include "BattleTank.h"

#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankPlayerController.h"
#include "TankTurret.h"
#include "TankTrack.h"

#include "Math/Rotator.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

#include "Components/InputComponent.h"
#include "Components/AudioComponent.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(TEXT("TankAimingComponent"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(TEXT("TankMovementComponent"));
	AddOwnedComponent(TankMovementComponent);
	AddOwnedComponent(TankAimingComponent);
	
	/* // set Pawn is automatically possessed by an AI Controller whenever it is created */
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ATank::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!ensure(PlayerInputComponent)) {UE_LOG(XXXXX_Log_BT, Error, TEXT("[BT][%s] NoPlayerInputComponent"), *this->GetName()); return;}

	PlayerInputComponent->BindAxis("BT_MouseX", this, &ATank::Turn);
	PlayerInputComponent->BindAxis("BT_MouseY", this, &ATank::LookUp);
	PlayerInputComponent->BindAxis("BT_ForwardBackward", this, &ATank::DriveForwardBackward);
	PlayerInputComponent->BindAxis("BT_TurnRightLeft", this, &ATank::TurnRightLeft);
	PlayerInputComponent->BindAxis("BT_TurnRightLeft", this, &ATank::TurnRightLeft);
	PlayerInputComponent->BindAction("BT_Fire", EInputEvent::IE_Pressed, this, &ATank::FirePressed);
	PlayerInputComponent->BindAction("BT_Fire", EInputEvent::IE_Released, this, &ATank::FireReleased);


}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TankInput.Sanitize();
}

void FTankInput::Sanitize()
{
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput.GetSafeNormal();
	RawMovementInput.Set(0.0f, 0.0f);

}

void FTankInput::MoveX(float AxisValue)
{
	RawMovementInput.X += AxisValue;
}

void FTankInput::MoveY(float AxisValue)
{
	RawMovementInput.Y += AxisValue;
}

void FTankInput::Fire(bool bPressed)
{
	bFire = bPressed;
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

void ATank::DriveForwardBackward(float Value)
{
	if (Value != 0.0f)
	{
		bDrivngForward = true;
		TankInput.MoveX(Value);
		OnDrivingForward.Broadcast(TankMovementComponent->IntendMoveForward(TankInput.MovementInput.X));
	}
	else
	{
		bDrivngForward = false;
		OnFwdBckwrdMovementStop();
	}
}

void ATank::TurnRightLeft(float Value)
{
	if (Value != 0.0f)
	{
		bTurning = true;
		TankInput.MoveY(Value);
		OnDrivingSide.Broadcast(TankMovementComponent->IntendTurnRight(TankInput.MovementInput.Y));
	}
	else
	{
		bTurning = false;
		OnLeftRightStop();
	}
}

void ATank::Fire()
{
	TankAimingComponent->Fire();
	PlayCameraShake(FireCameraShake,1.f);
}

void ATank::FirePressed()
{
	TankInput.Fire(true);
	Fire();
}

void ATank::FireReleased()
{
	TankInput.Fire(false);
}

bool ATank::PlayCameraShake(TSubclassOf<UCameraShake> CameraShakeToPlayType, float Scale, ECameraAnimPlaySpace::Type PlaySpace)
{
	if (CameraShakeToPlayType)
	{
		UGameplayStatics::GetPlayerController(this, 0)->ClientPlayCameraShake(CameraShakeToPlayType, Scale, PlaySpace);
		return true;
	}
	UE_LOG(XXXXX_Log_BT, Error, TEXT("[BT] [%s] CameraShakeToPlayType is not valid. Check BPs default reference is set "), *this->GetName());
	return false;
}

void ATank::Init()
{
	CurrentHealth = StartingHealth;
	if (EngineSound)
	{
		SetupEngineSounds(EngineSound);
	}
	else { UE_LOG(XXXXX_Log_BT, Error, TEXT("@@@@@ [%s] has no EngineSound set in BPs defaults"), *this->GetName()); }
	
	// Initialise TankPlayerController stuff which depends ond valid Tank
	if (GetController<ATankPlayerController>())
	{
		Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->PostTankInit(this);
	}
}

float ATank::GetHealthPercent() const
{

	return (float)CurrentHealth / (float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
		GetWorldTimerManager().SetTimer(RestartAfterDeathTimer, this, &ATank::RestartLevelWhenPlayerDie, 3.f);
	}
	return DamageToApply;
}

void ATank::RestartLevelWhenPlayerDie()
{
	ATankPlayerController* PC = Cast<ATankPlayerController>(GetController());
	if (PC)
	{
		PC->RestartLevel();
	}
}

////////////////////  IDamageInterface  //////////////////////
#pragma region IDamageInterface

void ATank::ReceiveDamage(float IncomingDamage)
{
	PlayCameraShake(FireCameraShake, 1.f);
}

float ATank::GetHealthRemaining()
{
	return 0.0f;
}

#pragma endregion IDamageInterface implementation

void ATank::StabilizeTurretYaw(float Throw) {

	// // Zeroing Turret rotation casued by tank rotation
	auto Turret = TankAimingComponent->GetTurret();
	if (!ensure(Turret)) { UE_LOG(XXXXX_Log_BT, Error, TEXT("[BT] [%s] TankAimingComponent has no Turret assigned !"), *this->GetName()); return;}
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
	UE_LOG(XXXXX_Log_BT, Log, TEXT("[BT] [%s] TrackOffset [%f] !"), *this->GetName(), LeftTrack->GetPositionOffset(LeftTrack->GetCurrentThrottle()));

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
	UE_LOG(XXXXX_Log_BT, Log, TEXT("[BT] [%s] SoundPitchMultipier [%f] !"), *this->GetName(), NewPitch)
	TankEngineAudioComp->SetPitchMultiplier(NewPitch);
}
