// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "RPS_UserWidget.h"
#include "RPS_ComboWidget.generated.h"

/**
 * 
 */
UCLASS()
class URPS_ComboWidget : public URPS_UserWidget
{
	GENERATED_BODY()
public:

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
