#include "TankMovementComponent.h"
#include "BattleTank.h"

#include "GameFramework/PlayerController.h"

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

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	bool bIsMovingForward = false;
	float OutThrow;
	IntendMoveForward(ForwardThrow, OutThrow);

	// // turning tank 
	bool bIsTurning = false;
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow, bIsTurning);
}

void UTankMovementComponent::CacheOwningTank()
{
	auto LocalTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (LocalTank)
	{
		OwningTank = LocalTank;
	}
}

bool UTankMovementComponent::IntendMoveForward(float Throw, float& OutThrow)
{
	bool bIsMoving = false;
	if (!ensure(LeftTrack && RightTrack)) { return false; }
	if (Throw != 0.f)
	{
		//!= 0.f
		bIsMoving = true;
		bDrivingForwardBackward = true;
		OutThrow = Throw;
		LeftTrack->SetThrottle(Throw, bIsMoving);
		RightTrack->SetThrottle(Throw, bIsMoving);
		GetOwningTank()->EnginePitchHandler();
		return bIsMoving;
	}
	else
	{
		bIsMoving = false;
		StopMovementImmediately();
		bDrivingForwardBackward = false;

	}
	OutThrow = Throw;
	return bIsMoving;
}

float UTankMovementComponent::IntendTurnRight(float Throw, bool& bIsMoving)
{
	if (!ensure(LeftTrack && RightTrack)) { return NULL; }
	if (Throw != 0)
	{
		if (bDrivingForwardBackward)
		{
			LeftTrack->SetThrottle(Throw * 0.5f, bIsMoving);
			RightTrack->SetThrottle(-Throw * 0.5f, bIsMoving);
		}
		else
		{
			LeftTrack->SetThrottle(Throw * 0.8f, bIsMoving);
			RightTrack->SetThrottle(-Throw * 0.8f, bIsMoving);
		}
		bIsMoving = true;
		GetOwningTank()->StabilizeTurretYaw(Throw);
		GetOwningTank()->EnginePitchHandler();
	}
	else
	{
		bIsMoving = false;
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
