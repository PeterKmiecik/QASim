// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPS_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class URPS_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	URPS_UserWidget(const FObjectInitializer& ObjectInitializer);

	/* similar to begin play*/
	virtual void NativeConstruct() override;

	void UpdateComboCount(int32 Value);

	void ResetCombo();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyProject", meta = (BindWidget))
	class UTextBlock* TXTCombo;

	class UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

	void StoreWidgetAnimations();

private:
	TMap < class FName, UWidgetAnimation* > AniamtionsMap;

	 UWidgetAnimation* ComboFadeAnimation;
	UWidgetAnimation* ComboShakeAnimation;

};
