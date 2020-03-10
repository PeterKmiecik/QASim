// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "BattleTank.h"
#include "Components/InputComponent.h"


ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!PlayerInputComponent) {
		UE_LOG(LogTemp, Error, TEXT("[%s] NoPlayerInputComponent"), *this->GetName());
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
