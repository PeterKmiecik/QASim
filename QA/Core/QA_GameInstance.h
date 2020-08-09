// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "QA_GameInstance.generated.h"

class UBPFL_Global;

/**
 * 
 */
UCLASS()
class QA_API UQA_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (KeyWords = "BPFL_Global object instance ref BPFL"), Category = "@@@ QA|QA_GameInstance")
	FORCEINLINE UBPFL_Global* GetBPFL_GlobalObject() const { return BPFL_GlobalObject; };
	void SetBPFL_GlobalObject(UBPFL_Global* InUBPFL_GlobalObject, UObject* WorldContextObject);
	UBPFL_Global* BPFL_GlobalObject;
protected:
	virtual void Init() override;

private:
	
};
