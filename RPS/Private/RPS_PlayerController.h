// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARPS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ARPS_PlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

/**
 * Temporary TEST
 */
	UFUNCTION(BlueprintCallable, Category = "@@@ RPS Controller")
	 void CallComboHit();


/**
* Temporary TEST
*/
	UFUNCTION(BlueprintCallable, Category = "@@@ RPS Controller")
	void ResetCombo();

	template <typename ASpawnBP>
	FORCEINLINE ASpawnBP* SpawnBP(
		UWorld* TheWorld,
		UClass* TheBP,
		const FVector& Loc,
		const FRotator& Rot,
		const bool bNoCollisionFail = true,
		AActor* Owner = NULL,
		APawn* Instigator = NULL
	)
	{
		if (!TheWorld) return NULL;
		if (!TheBP) return NULL;
		//~~~~~~~~~~~

		FActorSpawnParameters SpawnInfo;
		//SpawnInfo.bNoCollisionFail = bNoCollisionFail;
		SpawnInfo.bNoFail = true;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.bDeferConstruction = false;

		return TheWorld->SpawnActor<ASpawnBP>(TheBP, Loc, Rot, SpawnInfo);
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SpawningBP)
	UClass* BPSpawning;

private:
	int32 CurrentComboCount;
	FTimerHandle ComboResetHandle;

};
