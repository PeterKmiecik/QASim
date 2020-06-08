// Copyright EmbraceIT Ltd.

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
	UFUNCTION(BlueprintPure, Category = "@@@ Tank")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

	UFUNCTION(BlueprintCallable, Category = "@@@ Tank")
	ATank* GetTankRef() { return this; }

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void LookUp(float Value);

	UFUNCTION()
	void Turn(float Value);

	/* 	// Zeroing Turret rotation casued by tank rotation */
	UFUNCTION()
	void StabilizeTurretYaw(float Throw);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "@@@ Tank")
	class UTankAimingComponent* TankAimingComponent;


private:
	ATank();

	FRotator TankRotationBeforeInput;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ Tank")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "@@@ Tank")
	int32 CurrentHealth; 



};
