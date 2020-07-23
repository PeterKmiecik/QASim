// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "BattleTank.h"

#include "BPFL_Global.h"

#include "VisualLogger/VisualLogger.h"
#include "NavigationSystem.h"
#include "Engine/Engine.h" 

#include "TankAimingComponent.h"
#include "Tank.h" 

// Depends on movement component via pathfinding system
ATankAIController::ATankAIController(){

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UpdateNavDataRef();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { UE_LOG(XXXXX_Log_BT, Warning, TEXT("[BT] [%s] PlayerTank or ControlledTank reference "), *this->GetName()); return; }

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

//----------------------------------------------------------------------//
// INITIALIZATION
//----------------------------------------------------------------------//


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::UpdateNavDataRef()
{
	ANavigationData* NavDataLocal = nullptr;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem)
	{
		 NavDataLocal = NavSystem->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
		 if (!ensure(NavSystem && NavDataLocal)) { UE_LOG(XXXXX_Log_BT, Warning, TEXT("[BT] [%s]  Can't find NavMesh (UNavigationSystemV1) on the map, or NavMeshData returns nullptr: UpdateNavDataRef() "), *this->GetName()); return; }
	}
	NavData = NavDataLocal;

}

void ATankAIController::OnPossedTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

//----------------------------------------------------------------------//
// VISUAL LOGGING
//----------------------------------------------------------------------//
#if ENABLE_VISUAL_LOG
void ATankAIController::GrabDebugSnapshot(FVisualLogEntry* Snapshot) const
{
	Super::GrabDebugSnapshot(Snapshot);
	const int32 CatIndex = Snapshot->Status.AddZeroed();
	FVisualLogStatusCategory& PlaceableCategory = Snapshot->Status[CatIndex];

	FVisualLogger& Vlog = FVisualLogger::Get();
	if (Vlog.IsRecording())
	{
		auto Tank = Cast<UTankAimingComponent>(GetPawn()->GetComponentByClass(UTankAimingComponent::StaticClass()));
		if (!ensure(Tank))
		{
			UE_LOG(XXXXX_Log_BT, Warning, TEXT("[BT] [%s] has Tank pointer empty "), *this->GetName());
			return;
		}

		PlaceableCategory.Category = TEXT("TankFired");
		PlaceableCategory.Add(TEXT("TankFired"), Tank->GetFiringState()==EFiringState::Firing ? TEXT("FIRED") : TEXT("NOT"));

	}
}
#endif
