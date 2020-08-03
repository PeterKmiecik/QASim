// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class QG_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	UFUNCTION(BlueprintCallable, Category = "@@@ QG|Grabber")
	void Grab();

	UFUNCTION(BlueprintCallable, Category = "@@@ QG|Grabber")
	void Release();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "@@@ QG|Grabber")
	void NotifyQuestActor(AActor* Actor);

	/* // Radius of sphere for sphere trace */
	float GetGrabRadius() { return GrabRadius; };
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "@@@ QG|Grabber")
	FVector GetMaxGrabLocation() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "@@@ QG|Grabber")
	FVector GetHoldLocation() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "@@@ QG|Grabber")
	UPhysicsHandleComponent* GetPhysicsComponent() const;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "@@@ QG|Grabber")
	float MaxGrabDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "@@@ QG|Grabber")
	float HoldDistance = 100.f;

private:
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|Grabber")
	bool TraceForPhysicsBodies(AActor*& HitActor, UPrimitiveComponent*& HitComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|Grabber")
	float GrabRadius = 0.f;
	
};
