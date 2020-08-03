#include "QG_LightSwitchSlot.h"

#include "QG_GlobalDefines.h"

#include "Interact/Interactables/QG_Lamp.h"

#include "Kismet/GameplayStatics.h"

#include "FirstPersonCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

AQG_LightSwitchSlot::AQG_LightSwitchSlot()
{
	RootComponent = InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch Mesh"));
	InteractableHelpText = (FString("Press E to toggle light "));

	PlayerCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	PlayerCollisionBox->SetupAttachment(RootComponent);
}

void AQG_LightSwitchSlot::Interact_Implementation()
{
	if (PlayerCharacter && (bSwitchInPlace == true))
	{
		if (Lamp)
		{
			Lamp->ToggleLight();
		}
		else
		{
			UE_LOG(XXXXX_Log_QG, Error, TEXT("@@@@@ [%s] Interact_Implementation() Lamp was not found (set reference in level via picker) "), *this->GetName());
		}
	}
}

void AQG_LightSwitchSlot::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerCollisionBox)
	{
		PlayerCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AQG_LightSwitchSlot::OnOverlapBegin);
		PlayerCollisionBox->OnComponentEndOverlap.AddDynamic(this, &AQG_LightSwitchSlot::OnOverlapEnd);
	}
}

void AQG_LightSwitchSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AQG_LightSwitchSlot::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		PlayerCharacter = Cast<AFirstPersonCharacter>(OtherActor);

		if (PlayerCharacter)
		{
			bPlayerInRange = true;
		}
	}
}

void AQG_LightSwitchSlot::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PlayerCharacter)
	{
		PlayerCharacter = nullptr;
		bPlayerInRange = false;
	}
}