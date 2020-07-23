#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|TankBarrel")
	float MaxDegreesPerSecond = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|TankBarrel")
	float MaxElevationDegrees = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|TankBarrel")
	float MinElevationDegrees = -40.f;
};
