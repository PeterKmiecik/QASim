// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Components/InputComponent.h"
#include "TankTurret.h"
#include "Math/Rotator.h"


ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(TEXT("TankAimingComponent"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(TEXT("TankMovementComponent"));
}

void ATank::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!ensure(PlayerInputComponent)) {
		UE_LOG(LogTemp, Error, TEXT("[BT][%s] NoPlayerInputComponent"), *this->GetName());
		return;}


	PlayerInputComponent->BindAxis("MouseX", this, &ATank::Turn);
	PlayerInputComponent->BindAxis("MouseY", this, &ATank::LookUp);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
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
	if (!ensure(Turret)) { UE_LOG(LogTemp, Warning, TEXT("[BT] [%s] TankAimingComponent has not Turret assigned !"), *this->GetName()); return;}
	if (Throw != 0)
	{
		float CurrentTurretRotation = Turret->GetComponentRotation().Yaw;
		float TankRotation = this->GetActorRotation().Yaw;
		float DeltaTankRotation = TankRotationBeforeInput.Yaw - TankRotation;
			//UE_LOG(LogTemp, Warning, TEXT("[%s] Relative toation: [%f]"), *this->GetName(), CurrentRotation.Yaw);
	
		DeltaTankRotation =  FMath::ClampAngle(DeltaTankRotation, -0.5f, 0.5f);
		FRotator Delta = FRotator(0.f, DeltaTankRotation, 0.f);
		Turret->bAbsoluteRotation = true;
		Turret->AddRelativeRotation(Delta.GetNormalized());
		//UE_LOG(LogTemp, Warning, TEXT("[BT] [%s] DeltaTankRotation is [%f]  and turret COMPONENT [%f] "), *this->GetName(), DeltaTankRotation, CurrentTurretRotation);
		
	}
	else {
	TankRotationBeforeInput = GetActorRotation();
	}

	//UE_LOG(LogTemp, Warning, TEXT("[BT] [%] FPlatformTime::Seconds() [%f]"), *this->GetName(), FPlatformTime::Seconds());


}


