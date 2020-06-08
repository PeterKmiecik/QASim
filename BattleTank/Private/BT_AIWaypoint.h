// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BT_AIWaypoint.generated.h"

UCLASS()
class ABT_AIWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABT_AIWaypoint();

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT_AIWaypoint")
	class UBillboardComponent* Billboard;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
