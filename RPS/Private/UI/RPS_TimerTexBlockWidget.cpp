// Peter Kmiecik Art All Rights Reserved
#include "RPS_TimerTexBlockWidget.h"
#include "Public/BPFL_Global.h"

#include "Components/TextBlock.h"

void URPS_TimerTexBlockWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TextBlock->CreateDefaultSubobject<UTextBlock>("TextBlock");
	UpdateTimer(RoundTime);

}

void URPS_TimerTexBlockWidget::NativeConstruct()
{
	if (!ensure(TextBlock))
	{
		UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [%s] NativeConstruct(): TextBlock not valid. Check it was created properly.  "), *this->GetName());
	}
}

void URPS_TimerTexBlockWidget::UpdateTimer(uint8 CurrentRoundTime)
{
	TextBlock->SetText(FText::FromString(FString::FromInt(RoundTime)));
}

void URPS_TimerTexBlockWidget::SetRoundTime(uint8 InTime)
{
	RoundTime = InTime;
}


