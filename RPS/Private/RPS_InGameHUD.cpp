// Peter Kmiecik Art All Rights Reserved


#include "RPS_InGameHUD.h"
#include "UserWidget.h"
#include "RPS_UserWidget.h"

ARPS_InGameHUD::ARPS_InGameHUD() {

}

void ARPS_InGameHUD::DrawHUD()
{
}

void ARPS_InGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ComboWidgetClass)
	{
		ComboWidget = CreateWidget<URPS_UserWidget>(GetWorld( ), ComboWidgetClass);
		if (ComboWidget)
		{
			ComboWidget->AddToViewport();
		}
		
	}
}

void ARPS_InGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARPS_InGameHUD::UpdateCombatCount(int32 Value)
{
	if (ComboWidget)
	{
		ComboWidget->UpdateComboCount(Value);
	}
}

void ARPS_InGameHUD::ResetCombo()
{
	if (ComboWidget)
	{
		ComboWidget->ResetCombo();
	}

}
