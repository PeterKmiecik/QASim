#include "Grabber.h"

#include "QG_GlobalDefines.h"

#include "Interact/QG_Interactable.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components\SceneComponent.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetPhysicsComponent()->SetTargetLocationAndRotation(GetHoldLocation(), GetComponentTransform().Rotator());
}

void UGrabber::Grab()
{
	AActor* HitActor;
	UPrimitiveComponent* HitComponent;
	if (TraceForPhysicsBodies(HitActor, HitComponent))
	{
		if (HitActor && HitComponent)
		{
			AQG_Interactable* Interactable = Cast<AQG_Interactable>(HitActor);
			if (Interactable && (Interactable->bCanBeGrabbed == false))
			{
				return;
			}
			HitComponent->SetSimulatePhysics(true);
			HitComponent->SetMobility(EComponentMobility::Movable);
			HitComponent->WakeRigidBody();
			GetPhysicsComponent()->GrabComponentAtLocationWithRotation(
				HitComponent,
				NAME_None,
				HitComponent->GetCenterOfMass(),
				FRotator());
			NotifyQuestActor(HitActor);
		}
	}
}

void UGrabber::Release()
{
	GetPhysicsComponent()->ReleaseComponent();
}


FVector UGrabber::GetMaxGrabLocation() const
{
	return GetComponentLocation() + GetComponentRotation().Vector() * MaxGrabDistance;
}

FVector UGrabber::GetHoldLocation() const
{
	return GetComponentLocation() + GetComponentRotation().Vector() * HoldDistance;
}

UPhysicsHandleComponent* UGrabber::GetPhysicsComponent() const
{
	return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

void UGrabber::NotifyQuestActor_Implementation(AActor* Actor) {
} 

bool UGrabber::TraceForPhysicsBodies(AActor*& HitActor, UPrimitiveComponent*& HitComponent)
{
	const TArray<AActor*> ActorsToIgnore;
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesArray; 
	objectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));
	FHitResult HitResult;
	bool bHitSuccesfull = false;

	bHitSuccesfull = UKismetSystemLibrary::SphereTraceSingleForObjects(
		this,
		GetOwner()->GetActorLocation(),
		GetMaxGrabLocation(),
		GetGrabRadius(), 
		objectTypesArray,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::Type::None,
		HitResult,true,
		FLinearColor::Blue, 
		FLinearColor::Red);

	if (bHitSuccesfull)
	{
		HitActor = HitResult.GetActor();
		HitComponent = HitResult.GetComponent();
	}
	return bHitSuccesfull;
} 