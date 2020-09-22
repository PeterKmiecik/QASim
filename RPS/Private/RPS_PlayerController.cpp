// Peter Kmiecik Art All Rights Reserved

#include "RPS_PlayerController.h"
#include "RPS_InGameHUD.h"
#include "BPFL_Global.h"


#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/StaticMeshActor.h"

ARPS_PlayerController::ARPS_PlayerController() {
	CurrentComboCount = 0;
}

void ARPS_PlayerController::BeginPlay()
{
	const FVector  GenSpawnLoc(0.0f, 0.0f, 0.0f);
	const FRotator GenSpawnRot(0.0f, 0.0f, 0.0f);
	
	AStaticMeshActor* SpawnedBP = SpawnBP<AStaticMeshActor>(GetWorld(), BPSpawning, GenSpawnLoc, GenSpawnRot);
}

void ARPS_PlayerController::Tick(float DeltaTime)
{

}

void ARPS_PlayerController::CallComboHit()
{
	ARPS_InGameHUD* InGameHud = Cast<ARPS_InGameHUD>(GetHUD());
	if (InGameHud)
	{
		CurrentComboCount += 1;
		InGameHud->UpdateCombatCount(CurrentComboCount);
	}
	else
	{
		UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [%s] InGameHud ref is nulltpr in CallComboHit()"),*this->GetName());
	}

	if (GetWorld()->GetTimerManager().IsTimerActive(ComboResetHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(ComboResetHandle,this,&ARPS_PlayerController::ResetCombo, 10.0f, false);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ComboResetHandle);

		GetWorld()->GetTimerManager().SetTimer(ComboResetHandle, this, &ARPS_PlayerController::ResetCombo, 10.0f, false);
	}
}

void ARPS_PlayerController::ResetCombo()
{
	CurrentComboCount = 0;
	ARPS_InGameHUD* InGameHud = Cast<ARPS_InGameHUD>(GetHUD());
	if (InGameHud)
	{
		InGameHud->ResetCombo();
	}
	else
	{
		UE_LOG(XXXXX_Log_RPS, Log, TEXT("@@@ [%s] InGameHud ref is nulltpr in ResetCombo()"), *this->GetName());
	}
}


