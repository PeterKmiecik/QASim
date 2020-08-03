#include "TankMovementComponent.h"
#include "BattleTank.h"

#include "GameFramework/PlayerController.h"
#include "AIController.h"

#include "BPFL_Global.h"

#include "TankTrack.h"
#include "Tank.h"

void UTankMovementComponent::Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	CacheOwningTank();

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	if (!LeftTrack && RightTrack)
	{
		UE_LOG(XXXXX_Log_BT, Warning, TEXT("[BT] [%s] has no TankTracks!"), *this->GetName());
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	// // MoveVelocity is direction to which AI would like to go, based on request from UNavMovementComponent
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	AIForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(AIForwardThrow);

	// // turning tank 
	AIRightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(AIRightThrow);
}

void UTankMovementComponent::CacheOwningTank()
{
	auto LocalTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (LocalTank)
	{
		Tank = LocalTank;
	}
}

float UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return false; }
	if (Throw != 0.f)
	{
		bDrivingForwardBackward = true;
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
		GetTank()->EnginePitchHandler();
	}
	else
	{
		bDrivingForwardBackward = false;
	}
	return Throw;
}

float UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return false; }
	if (Throw != 0.f)
	{
		if (bDrivingForwardBackward)
		{
			LeftTrack->SetThrottle(Throw * DrivingTurnSpeedMultiplier);
			RightTrack->SetThrottle(-Throw * DrivingTurnSpeedMultiplier);
		}
		else
		{
			LeftTrack->SetThrottle(Throw * InPlaceTurnSpeedMultiplier);
			RightTrack->SetThrottle(-Throw * InPlaceTurnSpeedMultiplier);
		}
		GetTank()->StabilizeTurretYaw(Throw);
		GetTank()->EnginePitchHandler();
	}
	return Throw;
}

TArray<UTankTrack*> UTankMovementComponent::GetTankTracks()
{
	TArray<UTankTrack*> ArrayOfTracks;
	if (LeftTrack && RightTrack)
	{
		ArrayOfTracks.Add(LeftTrack);
		ArrayOfTracks.Add(RightTrack);
	}
	return ArrayOfTracks;
}
