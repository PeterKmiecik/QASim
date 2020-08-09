#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "VisualLogger/VisualLogger.h"

#include "TankMovementComponent.generated.h"

class UTankTrack;
class ATank;


/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankMovementComponent")
	void Init(class UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	/* // Called from BP
	* @return true if we are moving
	*/
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankMovementComponent")
	float IntendMoveForward(float Throw);

	/* // Called from BP
	* @return true if we are moving
	*/
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankMovementComponent")
	float IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankMovementComponent")
	TArray<UTankTrack*> GetTankTracks();

	FORCEINLINE UTankTrack* GetLeftTrack() const { return LeftTrack; };
	FORCEINLINE UTankTrack* GetRightTrack() const { return RightTrack; };
protected:

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ BT|Tank|TankMovementComponent|AI")
	float AIForwardThrow = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ BT|Tank|TankMovementComponent|AI")
	float AIRightThrow = 0.f;

	/* // Turning Speed multiplier for when we are driving and turning */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ BT|Tank|TankMovementComponent|AI")
	float DrivingTurnSpeedMultiplier = 0.5f;

	/* // Turning Speed multiplier for when we are driving and turning */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ BT|Tank|TankMovementComponent|AI")
	float InPlaceTurnSpeedMultiplier = 0.8f;

	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	FORCEINLINE ATank* GetTank() const { return Tank; };

	void CacheOwningTank();
	ATank* Tank;

	bool bDrivingForwardBackward = false;
};
