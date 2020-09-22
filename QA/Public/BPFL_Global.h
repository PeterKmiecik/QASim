// Peter Kmiecik Art All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_Global.generated.h"

 // Log categories declarations // 
QA_API DECLARE_LOG_CATEGORY_EXTERN(XXXXX_Log_QA, Log, All);
QA_API DECLARE_LOG_CATEGORY_EXTERN(XXXXX_Log_SHMUP, Log, All);
QA_API DECLARE_LOG_CATEGORY_EXTERN(XXXXX_Log_RPS, Log, All);
/* // VisualLogger log categories */
DEFINE_LOG_CATEGORY_STATIC(LogVL, Log, All);

/** Usable for logging out Enum state name.
* @param  EnumClassName - pass enum variable
* @param  ValueOfEnum - pass enuum value 
* @return  Name of enum. 
*/
#define ENUM_TO_STRING(EnumClassName, ValueOfEnum) UBPFL_Global::GetEnumValueAsString<EnumClassName>(FString(TEXT(#EnumClassName)), (ValueOfEnum))

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

	/** Get Name of Enum as String. USE: ENUM_TO_STRING(EnumClassName, ValueOfEnum)  MACRO */
	template<typename TEnum>
	static FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!enumPtr)
		{
			return FString("Invalid");
		}
		return enumPtr->GetNameByValue((int64)Value).ToString();
	}

	/** Spwans UserWidget to viewport if doesn't yet exist, if it exists does notj
	* fails if WidgetClass reference is not set in BPs
	* @param WidgetClass - widget class type to spawn, should be set in BPs !
	* @param UserWidget - variable to which spawned widget instance should be pointed to
	*/
	template<typename TWidgetClass, typename TWidget>
	FORCEINLINE static void SpawnWidgetToViewport(UObject* WorldContextObject, TSubclassOf <TWidgetClass> WidgetClass, TWidget* & UserWidget)
	{
		if (!WorldContextObject)
		{
			UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [QA] [BPFL_Global] SpawnWidgetToViewport(...): not valid WorldContextObject "));
			return;
		}
		if (!GEngine)
		{
			UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [QA] [BPFL_Global] SpawnWidgetToViewport(...): not valid GEngine"));
			return;
		}

		UWorld* const MyWorld = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
		check(MyWorld);
		if (!WidgetClass)
		{
			UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [QA] [BPFL_Global] WidgetClass not valid, check if the reference is set in BPs "));
		}


		UserWidget = CreateWidget<TWidgetClass>(MyWorld->GetWorld(), WidgetClass);
		if (UserWidget)
		{
			UserWidget->AddToViewport();
		}
		else
		{
			UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [QA] [BPFL_Global] SpawnWidgetToViewport(...): [%s] UserWidget [%s] not created = nullptr after CreateWidget"), *WorldContextObject->GetName(), *WidgetClass->GetName());
		}
	}

private:
	/** Called by [UBPFL_Global] OpenLevel(...) to allow delay with TimerHandle*/
	UFUNCTION()
	void OpenLevelDelayed(bool LevelNameWasSplit, UObject* WorldContextObject, FName LevelToLoadName);
};