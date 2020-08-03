// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QG_BPFL.generated.h"

/**
 * 
 */
UCLASS()
class QG_API UQG_BPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

/**
* // Spawns QuestManager actor if it does not exist
* @return Pointer to spawned QuestManager BP actor
*/
	UFUNCTION(BlueprintCallable, Category = "@@@ QG|BPFL", meta = (WorldContext = "WorldContextObject", Keywords = "get quest manager"))
	static class AQuestManager* GetQuestManager(const UObject* WorldContextObject);

/**
* // Spawns actor and returns its BP object type reference
* @param TheBP - WARNING: must set (in BP) blueprint class reference on class which will spawn this actor!
* @return Pointer to BP class which will be spawned

 // example call: AQuestManager* NewActor = SpawnBP<AQuestManager>(GetWorld(), BPSpawning, GenSpawnLoc, GenSpawnRot);

   https://answers.unrealengine.com/questions/187297/view.html
   https://www.ue4community.wiki/Legacy/Templates_in_C%2B%2B
*/
	template <typename ASpawnBP>
	static FORCEINLINE  ASpawnBP* SpawnBP(
		UWorld* TheWorld,
		UClass* TheBP,
		const FVector& GenSpawnLoc = FVector(0.0f, 0.0f, 0.0f),
		const FRotator& GenSpawnRot = FRotator(0.0f, 0.0f, 0.0f),
		const bool bNoCollisionFail = true,
		AActor* Owner = NULL,
		APawn* Instigator = NULL
	)
	{
		if (!TheWorld)	return NULL;
		if (!TheBP) return NULL;
		//~~~~~~~~~~~

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.bNoFail = true;
		//SpawnInfo.bNoCollisionFail = bNoCollisionFail;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.bDeferConstruction = false;

		return TheWorld->SpawnActor<ASpawnBP>(TheBP, GenSpawnLoc, GenSpawnRot, SpawnInfo);
	}
};
