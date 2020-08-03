// Fill out your copyright notice in the Description page of Project Settings.


#include "QG_QuestTriggerVolume.h"
#include "Components\BoxComponent.h"
#include "QG_BPFL.h"
#include "QG_GlobalDefines.h"
#include "Quests\QuestManager.h"

AQG_QuestTriggerVolume::AQG_QuestTriggerVolume() {

	GetCollisionComponent()->bVisible = true;
	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCollisionComponent()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetCollisionComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetCollisionComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	bCompleteWholeQuest = false;
	QuestIdWarning ="" ;
}

void AQG_QuestTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

// TODO: Build Error: its not a memeber of this or parent calsses
//void AQG_QuestTriggerVolume::PostEditChangeProperty(struct FPropertyChangedEvent& e)
//{
//	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
//	if (PropertyName == GET_MEMBER_NAME_CHECKED(AQG_QuestTriggerVolume, QuestId))
//	{
//			IsQuestIdValid();
//	}
//	Super::PostEditChangeProperty(e);
//}

void AQG_QuestTriggerVolume::Initialize()
{
	QuestManager = UQG_BPFL::GetQuestManager(GetWorld());
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AQG_QuestTriggerVolume::OnOverlapBegin);
}

void AQG_QuestTriggerVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsQuestIdValid())
	{
		auto Pawn = Cast<APawn>(OtherActor);
		if (Pawn)
		{
			QuestManager->CompleteQuest(QuestId, bCompleteWholeQuest);
		}
		else
		{
			UE_LOG(XXXXX_Log_QG, Log, TEXT("@@@ [%s] overlapped not APawn "), *(this->GetName()));
		}
	}
	else
	{
		UE_LOG(XXXXX_Log_QG, Warning, TEXT("@@@ [%s] OnOverlapBegin(...) IsQuestIdValid() returns false"), *(this->GetName()));
	}
}

bool AQG_QuestTriggerVolume::IsQuestIdValid() 
{
	if (!QuestManager)
	{
		UE_LOG(XXXXX_Log_QG, Warning, TEXT("@@@ [%s] QuestManager Not valid"), *(this->GetName()));
		return false;
	}
	for (auto x : QuestManager->GetQuests())
	{
		if (x.QuestId == QuestId)
		{
			QuestIdWarning = "Id OK";
			return 	bQuestIdValid = true;
		}
	}
	UE_LOG(XXXXX_Log_QG, Warning, TEXT("@@@ There is no record of provided QuestId by [%s] in QuestManager list of quests. "), *(this->GetName()));
	QuestIdWarning = "This QuestId is incompatible with list of quests ! check any typos!";
	return bQuestIdValid = false;
}

