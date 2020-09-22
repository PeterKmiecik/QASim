// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "RPS_UserWidget.h"
#include "RPS_TimerTexBlockWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class URPS_TimerTexBlockWidget : public URPS_UserWidget
{
	GENERATED_BODY()
public:

	void UpdateTimer(uint8 CurrentRoundTime);
	void SetRoundTime(uint8 InTime);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
private:
	uint8 RoundTime;


	UTextBlock* TextBlock;

};
