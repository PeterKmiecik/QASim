// Fill out your copyright notice in the Description page of Project Settings.


#include "QG_QuestTriggerCollect.h"
#include "QG_BPFL.h"
#include "QG_GlobalDefines.h"
#include "Quests\QuestManager.h"
#include "Components\BoxComponent.h"

AQG_QuestTriggerCollect::AQG_QuestTriggerCollect()
{
	GetCollisionComponent()->bVisible = true;
	GetCollisionComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCollisionComponent()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetCollisionComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetCollisionComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	GetCollisionComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);

	QuestIdWarning = "";
	bCompleteWholeQuest = false;

}

void AQG_QuestTriggerCollect::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void AQG_QuestTriggerCollect::Initialize()
{
	QuestManager = UQG_BPFL::GetQuestManager(GetWorld());
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AQG_QuestTriggerCollect::OnOverlapBegin);
}

// TODO: Build Error: its not a memeber of this or parent calsses
//void AQG_QuestTriggerCollect::PostEditChangeProperty(struct FPropertyChangedEvent& e)
//{
//	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
//	if (PropertyName == GET_MEMBER_NAME_CHECKED(AQG_QuestTriggerCollect, QuestId))
//	{
//		IsQuestIdValid();
//	}
//	Super::PostEditChangeProperty(e);
//}

void AQG_QuestTriggerCollect::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsQuestIdValid())
	{
		if (IsCorrectItem(OtherActor) && HasNotSeenItem(OtherActor))
		{
			MarkItemSeen(OtherActor);
			NotifyQuestComplete();
		}
	} else { UE_LOG(XXXXX_Log_QG, Warning, TEXT("@@@ [%s] OnOverlapBegin(...) IsQuestIdValid() returns false"), *(this->GetName())); }
}

bool AQG_QuestTriggerCollect::IsQuestIdValid()
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

bool AQG_QuestTriggerCollect::IsCorrectItem(AActor* InActor)
{
	return 	InActor->ActorHasTag(ItemTag);
}

void AQG_QuestTriggerCollect::MarkItemSeen(AActor* NewItem)
{
	if (NewItem)
	{
		SeenItems.Add(NewItem);
	}
	else
	{
		UE_LOG(XXXXX_Log_QG, Warning, TEXT("@@@ [%s] MarkItemSeen(...) parameter NewItem was not valid "), *(this->GetName()));
	}
}

void AQG_QuestTriggerCollect::NotifyQuestComplete()
{
	if (QuestManager)
	{
		QuestManager->CompleteQuest(QuestId, false);
	}
}

bool AQG_QuestTriggerCollect::HasNotSeenItem(AActor* ItemToFind)
{
	return !GetSeenItems().Contains(ItemToFind);
}