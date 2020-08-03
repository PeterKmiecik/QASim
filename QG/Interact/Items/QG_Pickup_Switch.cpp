#include "QG_Pickup_Switch.h"

#include "Interact/Interactables/QG_LightSwitchSlot.h"

#include "QG_GlobalDefines.h"

#include "Kismet/GameplayStatics.h"

#include "FirstPersonCharacter.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


AQG_Pickup_Switch::AQG_Pickup_Switch()
{
	
}

void AQG_Pickup_Switch::Use_Implementation()
{
	if (LightSwitchSlot->bSwitchInPlace == true) return;
	
	if (LightSwitchSlot && (LightSwitchSlot->bPlayerInRange == true))
	{
		this->bHidden = false;
		InteractableMesh->SetVisibility(true);
		FVector Transform = LightSwitchSlot->GetActorLocation();
		TeleportTo(Transform, FRotator::ZeroRotator);
		this->AttachToActor(LightSwitchSlot,FAttachmentTransformRules::SnapToTargetNotIncludingScale,(TEXT("SwitchSocket")));
		this->DisableComponentsSimulatePhysics();
		LightSwitchSlot->bSwitchInPlace = true;
		bCanInteract = false;
		bCanBeGrabbed = false;
	}
	else if (LightSwitchSlot && (LightSwitchSlot->bPlayerInRange == false))
	{
	LightSwitchSlot->bSwitchInPlace = false;
	FVector Transform = UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation();
	TeleportTo(Transform,FRotator::ZeroRotator);
	this->bHidden = false;
	InteractableMesh->SetVisibility(true);
	InteractableMesh->SetSimulatePhysics(true);
	InteractableMesh->WakeRigidBody();
	InteractableMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	InteractableMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AQG_Pickup_Switch::BeginPlay()
{
	Super::BeginPlay();
}
