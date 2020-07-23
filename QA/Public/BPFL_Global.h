// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_Global.generated.h"

/**
 * 
 */

 // Log declarations // 
DECLARE_LOG_CATEGORY_EXTERN(LogQA, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSHMUP, Log, All);
/* // VisualLogger */

DEFINE_LOG_CATEGORY_STATIC(LogVL, Log, All);


UCLASS(Blueprintable)
class QA_API UBPFL_Global : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UBPFL_Global();

};
