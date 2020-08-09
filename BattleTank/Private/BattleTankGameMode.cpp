
#include "BattleTankGameMode.h"
#include "BattleTank.h"

ABattleTankGameMode::ABattleTankGameMode()
{
	BT_PlayState = EBT_PlayState::EBT_InMainMenu;
}

void ABattleTankGameMode::HandleNewPlayState(EBT_PlayState NewState)
{
	switch (BT_PlayState)
	{
	case EBT_PlayState::EBT_Playing:
		break;
	case EBT_PlayState::EBT_GameOver:
		break;
	case EBT_PlayState::EBT_MatchWon:
		break;
	case EBT_PlayState::EBT_InPause:
		break;
	case EBT_PlayState::EBT_InMainMenu:
		break;
	case EBT_PlayState::EBT_Unknown:
	{ /* DO NOTHING */ }
		break;
	default:
		break;
	}
}

void ABattleTankGameMode::SetCurrentPlayState(EBT_PlayState NewState)
{
	//set current state
	BT_PlayState = NewState;
	// handle the new current state
	HandleNewPlayState(BT_PlayState);
}
