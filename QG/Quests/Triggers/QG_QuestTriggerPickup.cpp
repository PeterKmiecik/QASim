// Fill out your copyright notice in the Description page of Project Settings.


#include "QG_QuestTriggerPickup.h"
#include "Quests\QG_BPFL_Quests.h"
#include "QG_BPFL.h"
#include "QG_GlobalDefines.h"

// Sets default values for this component's properties
UQG_QuestTriggerPickup::UQG_QuestTriggerPickup()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UQG_QuestTriggerPickup::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQG_QuestTriggerPickup::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQG_QuestTriggerPickup::Pickup()
{
	if (UQG_BPFL::GetQuestManager(Cast<UObject>(GetWorld())))
	{

	}
	else
	{
		UE_LOG(XXXXX_Log_QG, Log, TEXT("[%s] Pickup() GetQuestManager() nullptr"), *this->GetName());
		return;
	}
}
