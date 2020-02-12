// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "SHMUP_BulletHell_PrimitiveComp.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class QA_API USHMUP_BulletHell_PrimitiveComp : public UPrimitiveComponent
{
	GENERATED_BODY()
	
public:
	USHMUP_BulletHell_PrimitiveComp();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnRegister() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "@@@ Comp")
	UStaticMeshComponent* ChildStaticMeshTest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@@@ Bullet Hell | Rotation")
	/* // Should BulletHell rotate all children components globally ? */
	bool bRotateAllSubComps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@@@ Bullet Hell | Rotation")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRotateToFaceOutwards;
	UPROPERTY()
	float OrbitDistance;
	float CurrentValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "@@@ Bullet Hell | Setup")
	TArray<FVector> FoundParentSockets;

	UFUNCTION(BlueprintCallable, Category = "@@@ Bullet Hell | Setup")
	/* // Searches for all sockets of parent Actor */
	TArray<FVector> FindSocketsSM();


	UFUNCTION(BlueprintCallable, Category = "@@@ Bullet Hell | Rotation")
	void RotateWithAllSubComps(float InRotationSpeed, float DeltaTime);


};
