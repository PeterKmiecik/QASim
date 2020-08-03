#pragma once

#include "CoreMinimal.h"
#include "Interact/QG_Interactable.h"
#include "QG_LightSwitchSlot.generated.h"

UCLASS()
class QG_API AQG_LightSwitchSlot : public AQG_Interactable
{
	GENERATED_BODY()
public:
	AQG_LightSwitchSlot();

	UPROPERTY(VisibleAnywhere, Category = "@@@ QG|AQG_LightSwitchSlot")
	bool bPlayerInRange = false;

	bool bSwitchInPlace = false;
	bool bCanInteract = false;

	UPROPERTY(EditAnywhere, Category = "@@@ QG|AQG_LightSwitchSlot")
	class UBoxComponent* PlayerCollisionBox;

	UPROPERTY(EditAnywhere, Category = "@@@ QG|AQG_LightSwitchSlot")
	class AQG_Lamp* Lamp;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void Interact_Implementation() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	class AFirstPersonCharacter* PlayerCharacter;
};