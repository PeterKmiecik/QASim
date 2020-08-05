#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankTankAimingComponent;
class ATank;
/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();
	/** // Called from Tank after he was initialized*/
	void PostTankInit(ATank* InTank);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "@@@ BT|PlayerController")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|PlayerController")
	void OnPossedTankDeath();

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|PlayerController")
	void Init();

	virtual void CreatePlayerUIWidget();

	/**~ WIDGETS -------------------------  */
	UPROPERTY(BlueprintReadOnly, Category = "@@@ BT|PlayerController")
	class UBT_UserWidget* PlayerUI;

	/* // Class to be set for Player tank UI HUD*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "@@@ BT|PlayerController")
	TSubclassOf< UBT_UserWidget> PlayerUIClass;
	/**~ WIDGETS -------------------------  */

private:
	ATank* ControlledTank;
	ATank* SetControlledTank(ATank* Tank);

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


