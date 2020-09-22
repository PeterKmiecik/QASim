// Peter Kmiecik Art All Rights Reserved
#include "RPS_GameMode.h"

#include "BPFL_Global.h"
#include "RPS_InGameHUD.h"
#include "UI/RPS_MainGameWidget.h"
#include "QA/Public/QA_Global_Defines.h"
#include "UI/RPS_TimerTexBlockWidget.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"


ARPS_GameMode::ARPS_GameMode()
{
	PlayableShape = EPlayableShape::EPS_null;
	RoundResult = ERoundResult::ERS_Null;
	PC = TEXT("PC");
	CPU = TEXT("CPU");
	bPlayerGoesFirst = false;
	TurnTimer = 30;
	MaxRounds = 10;
}

void ARPS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(XXXXX_Log_RPS, Log, TEXT("@@@ [%s] GAME MODE BEGIN PLAY "), *this->GetName());
	Init();
}

void ARPS_GameMode::Init()
{

}

void ARPS_GameMode::PlayRound(EPlayableShape InShape)
{
	StartRoundTimer(TurnTimeElapsed());
	GetInGameHUD()->PlayMainGame();

	//TODO check which round is it and pass data to HUD using CalcRound() <- Make "Turn: 3" widget in hud

	// TODO: FFighterData
	PlayerShape = InShape;
	SetRandCPUShape();
	
	// based on who calls it player/cpu, change their hand texture 
	DetermineAttackImage(PlayerShape, PC);
	DetermineAttackImage(PlayerShape, CPU);

	//PLAY FIGHT ANIMATION
	if (DeterminePlayerRoundPriority())
	{
		//player goes first -> make widgets appear for him first.
		if (GetInGameHUD())
		{
			GetMainGameWidget()->GetPlayerShapesButtonsBox()->SetIsEnabled(false);
		}
	} 
	//PLAY FIGHT ANIMATION
	GetMainGameWidget()->PlayAttackAnimation(GetMainGameWidget()->GetAttackAnimation());
}

ARPS_InGameHUD* ARPS_GameMode::GetInGameHUD()
{
	if (!RPS_InGameHUD) {
		RPS_InGameHUD = Cast<ARPS_InGameHUD>(HUDClass);
		if (!RPS_InGameHUD)
		{
			UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [%s] GetInGameHUD() failed to cast RPS_InGameHUD from HUDClass"), *this->GetName());
			return nullptr;
		}
	}
	return RPS_InGameHUD;
}

void ARPS_GameMode::SetRandCPUShape()
{
	uint8 n = FMath::RandRange(0, (uint8)EPlayableShape::EPS_null - 1);

	//FFighterData
	CPUShape = (EPlayableShape)n;
#if WITH_EDITOR
	UE_LOG(XXXXX_Log_RPS, Log, TEXT("@@@ [%s] SetRandCPUShape() has choosen random: [%s] CPU shape "), *this->GetName(), *ENUM_TO_STRING(EPlayableShape, CPUShape));
#endif //WITH_EDITOR end
}

URPS_MainGameWidget* ARPS_GameMode::GetMainGameWidget()
{
	return GetInGameHUD()->GetMainGameWidget();
}

void ARPS_GameMode::DetermineAttackImage(EPlayableShape ActiveHandType, FName ForWho)
{
	switch (ActiveHandType)
	{
	case EPlayableShape::EPS_Rock:
		ChangeAttackTexture(ActiveHandType,ForWho);
		break;
	case EPlayableShape::EPS_Paper:
		ChangeAttackTexture(ActiveHandType, ForWho);
		break;
	case EPlayableShape::EPS_Scissors:
		ChangeAttackTexture(ActiveHandType, ForWho);
		break;
	case EPlayableShape::EPS_null:
		break;
	default:
		break;
	}
}

void ARPS_GameMode::ChangeAttackTexture(EPlayableShape ActiveHandType, FName ForWho)
{
	if (ForWho == PC)
	{
		GetMainGameWidget()->GetPlayerHandImage()->SetBrushFromTexture(GetMainGameWidget()->GetPlayableShape2DTexture(ActiveHandType));
	}
	else
	{
		GetMainGameWidget()->GetCpuHandImage()->SetBrushFromTexture(GetMainGameWidget()->GetPlayableShape2DTexture(ActiveHandType));
	}
}

bool ARPS_GameMode::DeterminePlayerRoundPriority()
{
	bPlayerGoesFirst = false;
	int Rand = (FMath::Rand())%2;
	// if remainder 0, random number is even
	if (Rand > 0)
	{
		bPlayerGoesFirst = true;
	}
	UE_LOG(XXXXX_Log_RPS, Log, TEXT("@@@ [%s] Random round start, first goes: %s"), *this->GetName());
	return bPlayerGoesFirst;
}

float ARPS_GameMode::TurnTimeElapsed()
{
	float SecondsFloat = GetWorld()->TimeSeconds;
	float RoundFrac =  FMath::Frac(SecondsFloat / TurnTimer);
	return RoundFrac * TurnTimer;
}

uint8 ARPS_GameMode::CalcRound()
{
	// time from level start. not including Pause time
	float SecondsFloat = GetWorld()->TimeSeconds;
	Round = FMath::FloorToFloat(SecondsFloat / TurnTimer);
	return Round;
}

void ARPS_GameMode::StartRoundTimer(float InTime)
{
	GetInGameHUD()->GetTurnTimerWidget()->SetRoundTime(InTime);

}