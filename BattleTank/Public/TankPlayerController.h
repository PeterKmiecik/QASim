// Copyright EmbraceIT Ltd.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class UTankTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "@@@ Tank Player Controller")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UFUNCTION()
	void OnPossedTankDeath();

private:

	/* WIDGETS -------------------------  */

	UPROPERTY(EditDefaultsOnly, Category = "@@@ Tank Player Controller")
	TSubclassOf<class UBT_UserWidget> wPlayerUI;

	UPROPERTY(BlueprintReadOnly, Category = "@@@ Tank Player Controller")
	UBT_UserWidget* PlayerUI;

	/* WIDGETS -------------------------  */

	void SetPawn(APawn * InPawn);
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ Tank Player Controller")
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ Tank Player Controller")
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ Tank Player Controller")
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
