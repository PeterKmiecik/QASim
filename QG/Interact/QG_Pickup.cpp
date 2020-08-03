#include "QG_Pickup.h"

#include "QG_GlobalDefines.h"

#include "Kismet/GameplayStatics.h"

#include "FirstPersonCharacter.h"
#include "Components/StaticMeshComponent.h"

AQG_Pickup::AQG_Pickup()
{
	RootComponent = InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	InteractableMesh->SetSimulatePhysics(true);

	ItemName = FString("Enter an item name here..");
	InteractableHelpText = FString("Press E to pickup item up.");
	Value = 0;
}

void AQG_Pickup::Use_Implementation()
{
	UE_LOG(XXXXX_Log_QG, Warning, TEXT("@@@@@ [%s] Use_Implementation() called from base AQG_Pickup Class but should not"), *this->GetName());
}

void AQG_Pickup::BeginPlay()
{
	InteractableHelpText = FString::Printf(TEXT("%s: Press E to pick up."), *ItemName);
}

void AQG_Pickup::Interact_Implementation()
{
	if (bCanInteract == true)
	{
		AFirstPersonCharacter* Character = Cast<AFirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

		if (Character->AddItemToInventory(this))
		{
			OnPickedUp();
		}
	}
}

void AQG_Pickup::OnPickedUp()
{
	InteractableMesh->SetVisibility(false);
	InteractableMesh->SetSimulatePhysics(false);
	InteractableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}