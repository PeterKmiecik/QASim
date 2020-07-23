// Fill out your copyright notice in the Description page of Project Settings.
#include "TankTrack.h"

#include "BattleTank.h"
#include "QA/Public/BPFL_Global.h"

#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"

#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "Tank.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	CacheTankRef();
}

void UTankTrack::Init()
{
	GetSprungWheels();
	GetWheelComps();
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ATank* UTankTrack::CacheTankRef()
{
	if (!Tank)
	{
		Tank = Cast<ATank>(this->GetOwner());
		if (!ensureAlways(Tank))
		{
			UE_LOG(XXXXX_Log_BT, Warning, TEXT("@@@@@ [%s] Cast to Tank ref failed "), *this->GetName());
		}
		return Tank;
	}
	return Tank;
}

TArray<USphereComponent*> UTankTrack::GetWheelComps()
{
	if (!ensureAlways(SprungWheels[0])) {	UE_LOG(XXXXX_Log_BT, Warning, TEXT("@@@@@ [%s] GetWheelComp() returns nullptr"), *this->GetName());
		return WheelSphereComponents; }
	
	for (ASprungWheel* SprungWheelInst : SprungWheels)
	{
		
		//auto Wheels = SprungWheelInst->GetComponentsByClass(USphereComponent::StaticClass());
		auto Wheels = SprungWheelInst->GetComponentsByTag(USphereComponent::StaticClass(), TEXT("Wheel_1"));
		for (UActorComponent* ActorComp : Wheels)
		{
			auto SphereComp = Cast<USphereComponent>(ActorComp);
			if (!SphereComp) continue;
			
			WheelSphereComponents.Add(SphereComp);
			// log content of array
			//UE_LOG(XXXXX_Log_BT, Log, TEXT("@@@@@ [%s] GetWheelComp() Array: %s"), *this->GetName(),*SphereComp->GetName());
		}
	}
	return WheelSphereComponents;
}

void UTankTrack::ToggleMovement(bool OnOrOff, float SlowAlpha) {
	ensure(Tank);
	auto RootTankSM = Cast<UStaticMeshComponent>(Tank->GetRootComponent());
	if (OnOrOff)
	{
		bTrackMoves = true;
		RootTankSM->WakeRigidBody();
		RootTankSM->SetLinearDamping(0.f);
		RootTankSM->SetAngularDamping(0.f);

		for (USphereComponent* SpawnedWheelComp : WheelSphereComponents)
		{
			if (SpawnedWheelComp)
			{
				SpawnedWheelComp->WakeRigidBody();
				SpawnedWheelComp->ShapeColor.Blue;
				SpawnedWheelComp->SetLinearDamping(10.f);
				SpawnedWheelComp->SetAngularDamping(1000.f);
			}
		}
	}
	else
	{
		bTrackMoves = false;
		for (USphereComponent* SpawnedWheelComp : WheelSphereComponents)
		{
			//SpawnedWheelComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector, false);
			//SpawnedWheelComp->SetPhysicsLinearVelocity(FVector::ZeroVector, false);

			SpawnedWheelComp->SetLinearDamping(FMath::Lerp(10.f, Tank->GetWheelAngularDampingToStop(), SlowAlpha));
			SpawnedWheelComp->SetAngularDamping(FMath::Lerp(10.f, Tank->GetWheelAngularDampingToStop(), SlowAlpha));

			SpawnedWheelComp->ShapeColor.Green;
			SpawnedWheelComp->ShapeColor.MakeRandomColor();
			//SpawnedWheelComp->PutRigidBodyToSleep();
		}
		RootTankSM->SetAngularDamping(FMath::Lerp(0.f, Tank->GetTankAngularDampingToStop(), SlowAlpha));
		RootTankSM->SetLinearDamping(FMath::Lerp(0.f, Tank->GetTankLinearDampingToStop(), SlowAlpha));
		//RootTankSM->PutRigidBodyToSleep();
	}
}

void UTankTrack::SetThrottle(float Throttle, bool IsMoving)
{
	CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto ForcePerWheel = ForceApplied / SprungWheels.Num();
	for (ASprungWheel* SprungWheelInst : SprungWheels)
	{
		SprungWheelInst->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetSprungWheels() 
{
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		ASprungWheel* SprungWheel = SpawnPointChild->GetSpawnedActor();
		//auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		SprungWheels.Add(SprungWheel);
	}
	if (SprungWheels.Num() <= 0)
	{
		UE_LOG(XXXXX_Log_BT, Warning, TEXT("@@@@@ GetWheels() returns empty Array of Wheels"));
		return SprungWheels;
	}
	return SprungWheels;
}


// // implement texture change when rotationg.
// heres another tutorial on making Tracked Vehicle in UE4 https://www.youtube.com/watch?v=nCYYWorsYpQ
#pragma region Tracks Texture

float UTankTrack::GetPositionOffset(float Throw)
{
	float WheelDrivingForce = TrackMaxDrivingForce / SprungWheels.Num();
	float DrivingDir = WheelDrivingForce * Throw;

	// multiply by DeltaSeconds for speed over time offset
	return DrivingDir * GetWorld()->GetDeltaSeconds() / TrackMaxDrivingForce;
}

float UTankTrack::SetOffsetL(float Throw)
{
	return OffsetL += GetPositionOffset(Throw);
}

float UTankTrack::UpdateForwardUVs(float Throw)
{
	// REMEMBER: in Blender figure out treadLength and how many TreadUVTiles for the final tank model
	// currently in BP we make UVOffsel smaller: dividing it by TrackMaxDrivingForce (so it spins slower)
	return  SetOffsetL(Throw);
}

float UTankTrack::UpdateRotationUVs(float Throw)
{
	// REMEMBER: in Blender figure out treadLength and how many TreadUVTiles for the final tank model
	// currently in BP we make UVOffsel smaller: dividing it by TrackMaxDrivingForce (so it spins slower)
	return SetOffsetL(Throw) ;
}
#pragma endregion Tileable tracks Texture setup

