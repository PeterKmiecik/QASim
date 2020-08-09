// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_Global.generated.h"


 // Log categories declarations // 
DECLARE_LOG_CATEGORY_EXTERN(XXXX_Log_QA, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(XXXXX_Log_SHMUP, Log, All);
/* // VisualLogger log categories */
DEFINE_LOG_CATEGORY_STATIC(LogVL, Log, All);

class UGameInstance;
class UQA_GameInstance;
/**
 * General project global helper functions
 */
UCLASS(Blueprintable)
class QA_API UBPFL_Global : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
/** // Returns How much FromActor is looking in direction of TargetActor, between <-1,1> range.
	* @param FromDirection - Actor to start calculation from (usually "this" actor)
	* @param TargetActor - target to which we want to find difference in angle
	*
	* @return Percentage of directional similarities between two Vectors
	* if vectors pararrel: 1
	* if at right angle: 0
	* if positive value: similiarity of sharp angle
	* if negative value: dissimilarity of angle e.g. wide angle (-1 means 100% dissimilar)
	* if parameters passed will be not valid, returns -2.f
*/
	UFUNCTION(BlueprintCallable, meta = (KeyWords = "Dot Product To Target Math"), Category = "@@@ QA|Math")
	static float DotToTarget(AActor* FromActor, AActor* TargetActor, FString FromWhereErrorMsg);

/** // Loads specified Level. Will load Empty level if specified level asset is not valid
	* Has TimerHandle to deffer loading by specified time.
	 * @param NextLevel - Level to load. If specified SoftObject will be not valid, will load Empty level instead and return " "
	 * @param Delay - delay amount to load the level
	 *
	 * @return Name of level passed to be loaded. If not valid - returns " "
*/
	UFUNCTION(BlueprintCallable, meta = (KeyWords = "open load level map", WorldContext = "WorldContextObject"), Category = "@@@ QA|Utilities")
	static FName OpenLevel(UObject* WorldContextObject, TSoftObjectPtr<UObject>NextLevel, float Delay, float TimerRate, FString FromWhereErrorMsg);

	/** @return BPFL_GlobalObject pointer reference */
	UFUNCTION(BlueprintCallable, meta = (KeyWords = "BPFL_Global object instance ref BPFL", WorldContext = "WorldContextObject"), Category = "@@@ QA|Utilities")
	static UBPFL_Global* GetBPFL_GlobalObject(UObject* WorldContextObject);

	/** Called by QA_GameInstance at Init()
	* Sets BPFL_GlobalObject pointer reference inside QA_GameInstance */
	UFUNCTION(meta = (KeyWords = "cache BPFL_GlobalObject", WorldContext = "WorldContextObject"), Category = "@@@ QA|Utilities")
	static void CacheBPFL_GlobalObjectRef(UQA_GameInstance* InGameInstance, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (KeyWords = "Get QA_ QA_GameInstance Game Instance", WorldContext = "WorldContextObject"), Category = "@@@ QA|Utilities")
	static UQA_GameInstance* GetQA_GameInstance(UObject* WorldContextObject);

private:
	/** Called by [UBPFL_Global] OpenLevel(...) to allow delay with TimerHandle*/
	UFUNCTION()
	void OpenLevelDelayed(bool LevelNameWasSplit, UObject* WorldContextObject, FName LevelToLoadName);
};