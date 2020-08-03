// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "QG_BPFL.h"
#include "QG_GlobalDefines.h"
// Sets default values
AQuestManager::AQuestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AQuestManager::CompleteQuest_Implementation(FName QuestId, bool CompleteWholeQuest)
{
	int32 QuestIndex = GetQuestIndex(QuestId);
	FQuestInfo Quest = QuestList[QuestIndex];
	if (CompleteWholeQuest)
	{
		QuestList[QuestIndex].Progress = Quest.ProgressTotal;
	}
	else
	{
		QuestList[QuestIndex].Progress = FMath::Min(Quest.Progress + 1, Quest.ProgressTotal);
	}
	CompletedQuest.Broadcast(QuestIndex);
}

FQuestInfo AQuestManager::GetQuest(FName QuestId) const
{
	return QuestList[GetQuestIndex(QuestId)];
}

bool AQuestManager::IsActiveQuest_Implementation(FName QuestId) const
{
	int32 QuestIndex = GetQuestIndex(QuestId);
	return IsActiveIndex(QuestIndex);
}

int32 AQuestManager::GetQuestIndex_Implementation(FName QuestId) const {
	
	for (int32 i = 0; i < GetQuests().Num(); i++)
	{
		FQuestInfo QInfo = GetQuests()[i];
		if (QuestId == QInfo.QuestId)
		{
			return i;
		}
	}
	UE_LOG(XXXXX_Log_QG, Warning, TEXT("@@@ [%s] GetQuestIndex_Implementation(...) returns -1 meaning QuestId passed into function as parameter isn't in the list of FQuestInfo in AQuestManager;"), *this->GetName());
	return -1;
}


bool AQuestManager::IsActiveIndex(int32 InIndex) const
{
	
	for (int32 i = 0; i < GetQuests().Num(); i++)
	{
		if (InIndex == i)
		{
			return true;
		}
		else
		{
			if (IsQuestComplete(GetQuests()[i]) == false)
			{
				return false;
			}
		}
	}
	return false;
}

void AQuestManager::IncrementProgress(FQuestInfo& InQuestInfo)
{
	InQuestInfo.ProgressTotal = UKismetMathLibrary::Min(InQuestInfo.Progress++, InQuestInfo.ProgressTotal);
}
