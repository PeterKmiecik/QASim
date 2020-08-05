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

/**
 * General project global helper functions
 */
UCLASS(Blueprintable)
class QA_API UBPFL_Global : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	/** Returns How much FromActor is looking in direction of TargetActor, between -1,1 range.
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
	static float DotToTarget(AActor* FromActor, AActor* TargetActor, FString WhereItWasCalledFromErrorMsg);

};
