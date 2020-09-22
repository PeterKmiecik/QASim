// Peter Kmiecik Art All Rights Reserved
#include "QA_GameInstance.h"

#include "BPFL_Global.h"

#include "Kismet/GameplayStatics.h"

void UQA_GameInstance::Init()
{
	UBPFL_Global::CacheBPFL_GlobalObjectRef(this,this);
}

//void UQA_GameInstance::SetBPFL_GlobalObject(UBPFL_Global* InUBPFL_GlobalObject)
//{
//
//}

void UQA_GameInstance::SetBPFL_GlobalObject(UBPFL_Global* InUBPFL_GlobalObject, UObject* WorldContextObject)
{
	if (!InUBPFL_GlobalObject)
	{
		UE_LOG(XXXXX_Log_QA, Error, TEXT("@@@ [QA] [BPFL_Global] function: SetUBPFL_GlobalObject(...): InUBPFL_GlobalObject parameter not vaild"));
		return;
	}
	Cast<UQA_GameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject))->BPFL_GlobalObject = InUBPFL_GlobalObject;
}
