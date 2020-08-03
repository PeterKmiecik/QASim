#include "QG_Lamp.h"

#include "QG_GlobalDefines.h"

#include "Interact/Interactables/QG_LightSwitchSlot.h"

#include "Engine/EngineTypes.h"
#include "Engine/World.h"

#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

AQG_Lamp::AQG_Lamp(){
	
	RootComponent = LampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LampMesh"));
	LampLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("LampLight"));
	LampLight->SetupAttachment(RootComponent);
	LampLight->bHiddenInGame = true;
}

void AQG_Lamp::ToggleLight()
{
	if (!LampLight) return;
	if (LightSwitchSlot && (LightSwitchSlot->bSwitchInPlace))
	{
		LampLight->bHiddenInGame = false;
		LampLight->Activate();
		LampLight->Intensity = 2000.f;
		LampLight->bVisible = true;
		if (LampMaterial)
		{
			LampMaterial->SetScalarParameterValue(TEXT("Emission"), LampMaterialEmissiveGlow);
		}
	}
}

void AQG_Lamp::Interact_Implementation()
{
	ToggleLight();
}

void AQG_Lamp::BeginPlay()
{
	Super::BeginPlay();
}
