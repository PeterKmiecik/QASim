#include "TankPlayerController.h"
#include "BattleTank.h"

#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "TankAimingComponent.h"

#include "Tank.h"
#include "BT_UserWidget.h"

ATankPlayerController::ATankPlayerController()
{
	ControlledTank = nullptr;
	
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ATankPlayerController::Init()
{

}

void ATankPlayerController::CreatePlayerUIWidget()
{
	//~ WIDGETS ------------ //
	if (PlayerUIClass)
	{
		PlayerUI = CreateWidget<UBT_UserWidget>(this, PlayerUIClass);
		if (PlayerUI)
		{
			PlayerUI->AddToViewport();
			SetInputMode(FInputModeGameOnly());
		}
	}
	else { UE_LOG(XXXXX_Log_BT, Error, TEXT("[%s] no widget assigned in BPs for PlayerUI"), *this->GetName()); }
	// WIDGETS ------------ //
}

void ATankPlayerController::PostTankInit(ATank* InTank)
{
	if (SetControlledTank(InTank))
	{
		// Subscribe our local method to the tank's death event
		ControlledTank->OnDeath.AddDynamic(this, &ATankPlayerController::OnPossedTankDeath);
	}
	CreatePlayerUIWidget();
}

ATank* ATankPlayerController::SetControlledTank(ATank* Tank)
{
	if (!Tank) {
		UE_LOG(XXXXX_Log_BT, Error, TEXT("[%s] SetControlledTank() Tank ref passed not valid"), *this->GetName());
		return nullptr; }
	if (Tank == ControlledTank)
	{ return ControlledTank; }
	ControlledTank = Tank;
	if (!ensure(ControlledTank)) {
		UE_LOG(XXXXX_Log_BT, Error, TEXT("[%s] ControlledTank not valid"), *this->GetName());
		return nullptr;
	}
	return ControlledTank;
}


void ATankPlayerController::OnPossedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

/*~ AIMING -----------------  ---------------- */
#pragma region Aiming

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // e.g. if not possessing

	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation) // Has "side-effect", is going to line trace
	{
		ControlledTank->GetTankAimingComponent()->AimAt(HitLocation);
	}
}

// //Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

// // linetrace from specified looking direction. 
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Camera)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}

// // "De-project" the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y, 
		CameraWorldLocation,
		LookDirection
	);
}
#pragma endregion Aiming
