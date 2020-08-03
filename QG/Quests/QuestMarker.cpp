// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestMarker.h"
#include "QG_GlobalDefines.h"
#include "QG_BPFL.h"

// Sets default values
AQuestMarker::AQuestMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	
	SetRootComponent(Root);
	ParticleSystem->SetupAttachment(Root);
}

void AQuestMarker::BeginPlay()
{
	Super::BeginPlay();

	AQuestManager* QM = UQG_BPFL::GetQuestManager(GetWorld());
	if (QM != nullptr )
	{
		QM->CompletedQuest.AddDynamic(this, &AQuestMarker::QuestUpdate);
	}
	else
	{
		UE_LOG(XXXXX_Log_QG, Log, TEXT("[%s] GetQuestManager in BeginPlaye fails"), *this->GetName());
	}


	RefreshVisibility();
}

void AQuestMarker::RefreshVisibility()
{
	AQuestManager* QM = UQG_BPFL::GetQuestManager(GetWorld());
	FQuestInfo Quest = QM->GetQuest(QuestName);
	bool Visibility = QM->IsActiveQuest(QuestName) && Quest.Progress == ShowAtProgress;
	ParticleSystem->SetVisibility(Visibility);
}

void AQuestMarker::QuestUpdate(int32 Index)
{
	RefreshVisibility();
}