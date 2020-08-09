#pragma once

#include "CoreMinimal.h"
#include "Interact/QG_Pickup.h"
#include "QG_Pickup_Switch.generated.h"

UCLASS()
class QG_API AQG_Pickup_Switch : public AQG_Pickup
{
	GENERATED_BODY()
public:
	AQG_Pickup_Switch();

	UPROPERTY(EditAnywhere, Category = "@@@ QG|AQG_Pickup_Switch")
	class AQG_LightSwitchSlot* LightSwitchSlot;

protected:
	virtual void Use_Implementation() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

};