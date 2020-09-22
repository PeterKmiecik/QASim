// Peter Kmiecik Art All Rights Reserved
#include "RPS_InGameHUD.h"
#include "UI/RPS_ComboWidget.h"
#include "UI/RPS_MainGameWidget.h"
#include "RPS_UserWidget.h"
#include "BPFL_Global.h"
#include "UI/RPS_TimerTexBlockWidget.h"

#include "UserWidget.h"

ARPS_InGameHUD::ARPS_InGameHUD() {
	PrimaryActorTick.bCanEverTick = true;
}

void ARPS_InGameHUD::BeginPlay()
{
	UE_LOG(XXXXX_Log_RPS, Log, TEXT("@@@ [%s] AHUD BEGIN PLAY "), *this->GetName());

	Super::BeginPlay();
	Init();
}

void ARPS_InGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ARPS_InGameHUD::Init()
{
	if (!ensure(MainGameWidgetClass && ComboWidgetClass && TurnTimerWidgetClass))
	{
		UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [%s] Check widget classes references are set in RPS_InGameHUD BP. One is nullptr"), *this->GetName());
	}



}

void ARPS_InGameHUD::OpenMainMenu()
{
	StopPlayingMainGame();
	// spawn main menu
}

void ARPS_InGameHUD::PlayMainGame()
{
	UBPFL_Global::SpawnWidgetToViewport(this, MainGameWidgetClass, MainGameWidget);
	UBPFL_Global::SpawnWidgetToViewport(this, ComboWidgetClass, ComboWidget);
	UBPFL_Global::SpawnWidgetToViewport(this, TurnTimerWidgetClass, TurnTimerWidget);
}

void ARPS_InGameHUD::StopPlayingMainGame()
{
	MainGameWidget->RemoveFromViewport();
	TurnTimerWidget->RemoveFromParent();
	ComboWidget->RemoveFromViewport();
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