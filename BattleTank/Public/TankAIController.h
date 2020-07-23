#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATankAIController();

	/* // Current instance of nav mesh data active in world */
	UPROPERTY(BlueprintReadOnly, Category = "@@@ BT|TankAIController")
	ANavigationData* NavData;

protected:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|TankAIController")
	float AcceptanceRadius = 8000;

private:

	UFUNCTION()
	/* // Update reference to current NavMesh instance avaible in map (world) */
	void UpdateNavDataRef();

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnPossedTankDeath();

	// TO DO update navmesh reference for random waypoints generation
	//UPROPERTY()
	//const ARecastNavMesh*  RecastNavMesh;

#if ENABLE_VISUAL_LOG
// Appends information about this actor to the visual logger.
	virtual void GrabDebugSnapshot(FVisualLogEntry* Snapshot) const override;
#endif
};
