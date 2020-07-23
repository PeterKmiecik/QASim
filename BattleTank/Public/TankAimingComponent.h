#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo,
	Firing
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|TankAimingComponent")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|TankAimingComponent")
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|TankAimingComponent")
	int32 GetRoundsLeft() const;

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|TankAimingComponent")
	UTankBarrel* GetBarrel() { return Barrel; };
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|TankAimingComponent")
	UTankTurret* GetTurret() { return Turret; };

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|TankAimingComponent")
	EFiringState GetTankFiringState() { return FiringState; };
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "@@@ BT|TankAimingComponent")
	EFiringState FiringState = EFiringState::Reloading;
private:
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|TankAimingComponent")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|TankAimingComponent")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|TankAimingComponent")
	float ReloadTimeInSeconds = 3;
	
	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|TankAimingComponent")
	int32 RoundsLeft = 3;

	double LastFireTime = 0;

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|TankAimingComponent")
		bool bShowAimingTargetTraceLine = false;

	bool bHasFired;

};
