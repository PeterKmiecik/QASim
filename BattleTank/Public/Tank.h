#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" 

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "@@@ BT|Tank")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank")
	ATank* GetTankRef() { return this; }

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void LookUp(float Value);

	UFUNCTION()
	void Turn(float Value);

	/* 	// Zeroing Turret rotation casued by tank rotation */
	UFUNCTION()
	void StabilizeTurretYaw(float Throw);

	void EnginePitchHandler();

	float GetWheelLinearDampingToStop() { return WheelLinearDampingToStop; }
	float GetWheelAngularDampingToStop() { return WheelAngularDampingToStop; }
	float GetTankLinearDampingToStop() { return TankLinearDampingToStop; }
	float GetTankAngularDampingToStop() { return TankAngularDampingToStop; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "@@@ BT|Tank")
	class UTankAimingComponent* TankAimingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "@@@ BT|Tank")
	class UTankMovementComponent* TankMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "@@@ BT|Tank")
	class USoundBase* EngineSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "@@@ BT|Tank")
	float LowEnginePitch = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "@@@ BT|Tank")
	float HighEnginePitch = 2.f;

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank")
	void Init();
private:
	ATank();

	FRotator TankRotationBeforeInput;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|Tank")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Tank")
	int32 CurrentHealth; 

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|Tank|Movement|TankTrack")
	float WheelLinearDampingToStop = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|Tank|Movement|TankTrack")
	float WheelAngularDampingToStop = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|Tank|Movement")
	float TankLinearDampingToStop = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|Tank|Movement")
	float TankAngularDampingToStop = 1000.f;

	void SetupEngineSounds(USoundBase* Sound);

	class UAudioComponent* TankEngineAudioComp;

};
