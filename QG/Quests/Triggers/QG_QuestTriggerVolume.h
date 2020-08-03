// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "QG_QuestTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class QG_API AQG_QuestTriggerVolume : public ATriggerBox
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ExposeOnSpawn = "true"), Category = "@@@ QG|QuestTriggerVolume")
	FName QuestId;

	UPROPERTY(VisibleInstanceOnly, meta = (DisplayAfter = "bQuestIdValid"), Category = "@@@ QG|QuestTriggerVolume")
	FString QuestIdWarning;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "@@@ QG|QuestTriggerVolume")
	bool bCompleteWholeQuest;
	
	AQG_QuestTriggerVolume();


	UFUNCTION()
	 void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	virtual void BeginPlay() override;

	// TODO: Build Error: its not a memeber of this or parent calsses
	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	UPROPERTY()
	class AQuestManager* QuestManager;

	/* // Check to see if QuestId specified in this instance of QuestTriggerVolume is compatible with list of quests.*/
	UFUNCTION()
	bool IsQuestIdValid();

	/* // Initialize runtime properties such Overlap binding, actor references etc.  */
	void Initialize();

	UPROPERTY(VisibleInstanceOnly, meta = (DisplayAfter = "QuestId"), Category = "@@@ QG|QuestTriggerVolume")
	bool bQuestIdValid;

};
 