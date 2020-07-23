#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

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
	UFUNCTION(BlueprintImplementableEvent, Category = "@@@ BT|PlayerController")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UFUNCTION()
	void OnPossedTankDeath();


	/* WIDGETS -------------------------  */

	UPROPERTY(BlueprintReadOnly, Category = "@@@ BT|PlayerController")
	class UBT_UserWidget* PlayerUI;

	UPROPERTY()
	TSubclassOf< UBT_UserWidget> wPlayerUI;

	/* WIDGETS -------------------------  */

private:



	void SetPawn(APawn * InPawn);
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|PlayerController")
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|PlayerController")
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|PlayerController")
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
