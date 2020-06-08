// Peter Kmiecik Art All Rights Reserved


#include "SHMUP_GameModeBase.h"
#include "SHMUP\Player\SHMUP_BasePawn.h"
#include "Engine/World.h"




// Called when the game starts or when spawned
void ASHMUP_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ASHMUP_BasePawn* BaseDefaultPawn = Cast<ASHMUP_BasePawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	 
	if (!ensure(BaseDefaultPawn)) {UE_LOG(LogTemp, Warning, TEXT("@@@@@ [%s]Default pawn empty"), *this->GetName());	return;}
	BaseDefaultPawn->ShipHasDied.AddUniqueDynamic(this, &ASHMUP_GameModeBase::OnShipDeath);
}
	
void ASHMUP_GameModeBase::OnShipDeath() {
	UE_LOG(LogTemp, Log, TEXT("@@@@@ [%s] BroadcastedShipDeath"), *this->GetName());
}
