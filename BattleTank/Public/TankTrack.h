#pragma once


#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"



/** * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	/* // Sets a throttle between -1 and +1 */
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankTrack")
	void SetThrottle(float Throttle);
	
	/* // Max force per track, in Newtons */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TrackMaxDrivingForce = 400000; // Assume 40 tonne tank, and 1g accelleration

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankTrack")
	float UpdateForwardUVs(float Throw);

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankTrack")
	float UpdateRotationUVs(float Throw);

	/* // // Max force per track, in Newtons */
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankTrack")
	TArray< ASprungWheel*> GetSprungWheels();

	UPROPERTY(BlueprintReadWrite, Category = "@@@ BT|Tank|TankTrack")
	bool bTrackMoves = false;

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankTrack")
	void ToggleMovement(bool OnOrOff, float SlowAlpha);
	
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankTrack")
	float GetCurrentThrottle() { return CurrentThrottle; };

	float GetLeftTrackOffset() {return OffsetL;};

	/* // Obtained byy multiplying time * speed (TrackMaxDrivingForce)
	// returns change in position in space according to current speed. */
	float GetPositionOffset(float Throw);
protected:

	UPROPERTY(BlueprintReadOnly, Category = "@@@ BT|Tank|TankTrack")
	float UVOffsetL;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Tank|TankTrack")
	 TArray<class ASprungWheel*> SprungWheels;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Tank|TankTrack")
	 TArray<class USphereComponent*> WheelSphereComponents;

	/* // *gets Array of all WheelComponents (USphereComponents) */
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|TankTrack")

	void Init();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	virtual void BeginPlay();
private:


	UTankTrack();

	TArray<class USphereComponent*> GetWheelComps();

	void DriveTrack(float InCurrentThrottle);

	class ATank* CacheTankRef();
	ATank* Tank;

	float SetOffsetL(float Throw);

	float OffsetL = 0.f;

	float ThrottleSize = 0.f;

	float CurrentThrottle = 0.f;
};
