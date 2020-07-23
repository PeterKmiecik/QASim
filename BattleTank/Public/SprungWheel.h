#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	ASprungWheel();
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	virtual void BeginPlay() override;
	
private:
	void SetupConstraint();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Tank|SprungWheel")
	class USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Tank|SprungWheel")
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Tank|SprungWheel")
	class UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Tank|SprungWheel")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	float TotalForceMagnitudeThisFrame = 0;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Tank|SprungWheel")
	float CurrentLinearDamping;
};
