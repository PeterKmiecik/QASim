#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	USpawnPoint();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class ASprungWheel* GetSpawnedActor() const { return SpawnedActor; }

protected:
	virtual void BeginPlay() override;

private:
	/* // Choose SprungWheel class which will be spawned as wheel */
	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|SpawnPoint")
	TSubclassOf<ASprungWheel> SpawnClass;
	
	UPROPERTY()
	ASprungWheel* SpawnedActor;
};
