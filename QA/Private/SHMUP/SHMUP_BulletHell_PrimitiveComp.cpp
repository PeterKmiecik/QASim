// Peter Kmiecik Art All Rights Reserved


#include "SHMUP_BulletHell_PrimitiveComp.h"
#include "Components/StaticMeshComponent.h"
#include "QA_Global_Defines.h"
#include "DrawDebugHelpers.h"


USHMUP_BulletHell_PrimitiveComp::USHMUP_BulletHell_PrimitiveComp() {

#ifdef QA_TESTING_CODE
	ChildStaticMeshTest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChildStaticMesh"));
#endif // QA_TESTING_CODE

	PrimaryComponentTick.bCanEverTick = true;

	bRotateAllSubComps = false;
	RotationSpeed = 0.f;
	CurrentValue = 0.f;
	OrbitDistance = 100.f;
	bRotateToFaceOutwards = true;

}

void USHMUP_BulletHell_PrimitiveComp::BeginPlay()
{
	Super::BeginPlay();
	// TESTING 
#ifdef QA_TESTING_CODE

	if (ChildStaticMeshTest != nullptr)
	{
		ChildStaticMeshTest->AttachToComponent(GetAttachmentRoot(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] AttachToComponent from constructor failed for [%s] "), (*this->GetName()), *(ChildStaticMeshTest->GetName()));
		return;
	}
#endif // QA_TESTING_CODE




}


void USHMUP_BulletHell_PrimitiveComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FindSocketsSM();


}

void USHMUP_BulletHell_PrimitiveComp::OnRegister() {
	Super::OnRegister();

}


TArray<FVector> USHMUP_BulletHell_PrimitiveComp::FindSocketsSM()
{

	if (GetOwner() != nullptr)
	{
		 for ( auto SMComp : GetOwner()->GetComponentsByClass(UStaticMeshComponent::StaticClass()))
		 {
			 auto SM = Cast<UStaticMeshComponent>(SMComp);

			 if (SM)
			 {
				 for (auto Name : SM->GetAllSocketNames())
				 {
					 FVector FoundSocketLocation = GetSocketLocation(Name);
					 
					 auto Transform = GetSocketTransform(Name, RTS_Actor);
					 UE_LOG(LogTemp, Warning, TEXT("[%s]"), *Transform.GetLocation().ToString());


					 FoundParentSockets.Add(FoundSocketLocation);
					// UE_LOG(LogTemp, Warning, TEXT("[%s]"), *Name.ToString());
					// UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FoundSocketLocation.ToString());

				 }
			 }
			 else
			 {
				 UE_LOG(LogTemp, Warning, TEXT("[%s] FindSocketsSM failed check for [%s]"), *this->GetName(),*SM->GetName());

			 }
			 
		 }
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] FindSocketsSM failed check GetOwner()"), *this->GetName());
	}

	return FoundParentSockets;
}

void USHMUP_BulletHell_PrimitiveComp::RotateWithAllSubComps(float InRotationSpeed, float DeltaTime)
{
#ifdef QA_TESTING_CODE

	if (bRotateAllSubComps == true)
	{
		float CurrentValueInRadians = FMath::DegreesToRadians<float>(CurrentValue);
		// // TODO change SetRelativeLocation to be called on ARRAY of all children
		SetRelativeLocation(FVector(OrbitDistance * FMath::Cos(CurrentValueInRadians), OrbitDistance * FMath::Sin(CurrentValueInRadians), RelativeLocation.Z));
		if (bRotateToFaceOutwards)
		{
			FVector LookDir = (RelativeLocation).GetSafeNormal();
			FRotator LookAtRot = LookDir.Rotation();
			SetRelativeRotation(LookAtRot);
		}
		CurrentValue = FMath::Fmod(CurrentValue + (RotationSpeed * DeltaTime), 360);
	}
#endif  // QA_TESTING_CODE
}



/*
class Bullet Hell
 Register SC ShootingComponents
	Find Sockets
	SpawnSC(by Sockets amount) 
	add each to Array

class SocketManager
	Global ShootingPattern
	Global Rotate
	Randomize Patterns




	--------------------------------------------------------------
class ShootingComponent SC
	
Shoot

bInherit Global Pattern From Parent ?


PatternManager
	Generate Random Pattern
	Generate Random Pattern with property Weights
	Speed
	Rotation
	Lock on target
	Aiming (following target)
	Randomness
	Number of shots Rows / Columns
	Acceleration

-------------------------------------

class Bullet
ParticleMovement
*/