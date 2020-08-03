// Fill out your copyright notice in the Description page of Project Settings.


#include "QG_BPFL.h"
#include "QG_GameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Quests\QuestManager.h"
#include "QG_GlobalDefines.h"

AQuestManager* UQG_BPFL::GetQuestManager(const UObject* WorldContextObject)
{
	if ( !WorldContextObject)
	{
		UE_LOG(XXXXX_Log_QG, Warning, TEXT(" [QG_BPFL] GetQuestManager(...) param: WorldContextObject NULL "));
		return nullptr;
	}

	auto QG_GMB = Cast<AQG_GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (QG_GMB)
	{
		if (QG_GMB->GetQuestManager())
		{
			return QG_GMB->GetQuestManager();
		}
		AQuestManager* NewActor = SpawnBP<AQuestManager>(QG_GMB->GetWorld(), QG_GMB->GetQuestManagerClass());
		if (!NewActor)
		{
			UE_LOG(XXXXX_Log_QG, Warning, TEXT("[QG_BPFL] GetQuestManager(...) failed to spawn valid quest manager"));
			return nullptr;
		}
		QG_GMB->SetQuestManager(NewActor);
		return QG_GMB->GetQuestManager();
	}
	else
	{
		UE_LOG(XXXXX_Log_QG, Warning, TEXT("[QG_BPFL] GetQuestManager(...) QG_GMB empty ref"));
		return nullptr;
	}
}
