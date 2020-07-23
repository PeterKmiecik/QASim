#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "VisualLogger/VisualLogger.h"

#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankMovementComponent")
	void Init(class UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	/* // Called from BP*/
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankMovementComponent")
	bool IntendMoveForward(float Throw, float& OutThrow);

	/* // Called from BP*/
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankMovementComponent")
	float IntendTurnRight(float Throw, bool& bIsMoving);
	
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankMovementComponent")
	TArray<UTankTrack*> GetTankTracks();

	UTankTrack* GetLeftTrack() { return LeftTrack; };
	UTankTrack* GetRightTrack() { return RightTrack; };

private:
	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	class  ATank* GetOwningTank() { return OwningTank; };
	
	void CacheOwningTank();
	ATank* OwningTank;

	bool bDrivingForwardBackward = false;
};
