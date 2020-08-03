// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestInfo.h"
#include "QuestManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCompletedQuestSignature, int32, Index);

UCLASS()
class QG_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "@@@ QG|QuestManager")
	FCompletedQuestSignature CompletedQuest;

	/* ----------------------- */
	AQuestManager();

	virtual void Tick(float DeltaTime) override;

	/* // BP NativeEvent call it when You want to complete quest
	@param CompleteWholeQuest: if no increment completion progress by one
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "@@@ QG|QuestManager")
	void CompleteQuest(FName QuestId, bool CompleteWholeQuest);

	/* // Return Quest based ib Id from global quests list*/
	UFUNCTION(BlueprintPure, Category = "@@@ QG|QuestManager")
	FQuestInfo GetQuest(FName QuestId) const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "@@@ QG|QuestManager")
	bool IsActiveQuest(FName QuestId) const;

	UFUNCTION(BlueprintPure, Category = "@@@ QG|QuestManager")
	FORCEINLINE TArray<FQuestInfo> GetQuests() const { return QuestList; }

	UFUNCTION(BlueprintPure, Category = "@@@ QG|QuestManager")
	FORCEINLINE  bool IsQuestComplete(FQuestInfo InQuestInfo) const { return InQuestInfo.Progress == InQuestInfo.ProgressTotal; }

	UFUNCTION(BlueprintCallable, Category = "@@@ QG|QuestManager")
	bool IsActiveIndex(int32 InIndex) const;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@@@ QG|QuestManager")
	TArray<FQuestInfo> QuestList;

	/* ----------------------- */

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "@@@ QG|QuestManager")
	int32 GetQuestIndex(FName QuestId) const;

private:
	UFUNCTION(BlueprintPure, Category = "@@@ QG|QuestManager")
	void IncrementProgress(FQuestInfo& InQuestInfo);
};
