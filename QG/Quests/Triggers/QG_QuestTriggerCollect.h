// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "QG_QuestTriggerCollect.generated.h"

/**
 * 
 */
UCLASS()
class QG_API AQG_QuestTriggerCollect : public ATriggerBox
{
	GENERATED_BODY()
public:

	AQG_QuestTriggerCollect();

protected:
	virtual void BeginPlay() override;

	// TODO: Build Error: its not a memeber of this or parent calsses
	//virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ExposeOnSpawn = "true"), Category = "@@@ QG|QuestTriggerCollect")
	bool bCompleteWholeQuest;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ExposeOnSpawn = "true"), Category = "@@@ QG|QuestTriggerCollect")
	FName QuestId;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ExposeOnSpawn = "true"), Category = "@@@ QG|QuestTriggerCollect")
	FName ItemTag;

	UPROPERTY(BlueprintReadOnly, BlueprintGetter = "GetSeenItems", SimpleDisplay, meta = (ExposeOnSpawn = "true"), Category = "@@@ QG|QuestTriggerCollect")
	TSet<AActor*> SeenItems;

	UFUNCTION(BlueprintPure, meta = (Keywords = "Is correct item quest trigger collect"), Category = "@@@ QG|QuestTriggerCollect")
	bool IsCorrectItem(class AActor* InActor);

	UFUNCTION(BlueprintCallable, meta = ( Keywords = "mark item seen quest trigger collect"), Category = "@@@ QG|QuestTriggerCollect")
	void MarkItemSeen(AActor* NewItem);

	UFUNCTION(BlueprintCallable, meta = ( Keywords = "notify quest complete quest trigger collect"), Category = "@@@ QG|QuestTriggerCollect")
	void NotifyQuestComplete();

	UFUNCTION(BlueprintCallable, meta = ( Keywords = "Has Not Seen Item quest trigger collect"), Category = "@@@ QG|QuestTriggerCollect")
	bool HasNotSeenItem(AActor* ItemToFind);

	UFUNCTION(BlueprintPure, meta = (Keywords = "get seen items trigger collect"), Category = "@@@ QG|QuestTriggerCollect")
	FORCEINLINE TSet<AActor*> GetSeenItems() const { return SeenItems; };

private:

	UPROPERTY()
	class AQuestManager* QuestManager;

	/* // Check to see if QuestId specified in this instance of QuestTriggerCollect is compatible with list of quests.*/
	UFUNCTION()
	bool IsQuestIdValid();

	/* // Initialize runtime properties such Overlap binding, actor references etc.  */
	void Initialize();

	UPROPERTY(VisibleInstanceOnly, meta = (DisplayAfter = "QuestId"), Category = "@@@ QG|QuestTriggerCollect")
	bool bQuestIdValid;

	UPROPERTY(VisibleInstanceOnly, meta = (DisplayAfter = "bQuestIdValid"), Category = "@@@ QG|QuestTriggerCollect")
	FString QuestIdWarning;



};
