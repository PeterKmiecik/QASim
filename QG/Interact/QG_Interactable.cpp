#include "QG_Interactable.h"

#include "QG_GlobalDefines.h"



AQG_Interactable::AQG_Interactable()
{
	PrimaryActorTick.bCanEverTick = false;
	InteractableHelpText = (FString("Press E to interact"));
}

void AQG_Interactable::BeginPlay()
{
	Super::BeginPlay();
	
}

void AQG_Interactable::Interact()
{
}

void AQG_Interactable::Interact_Implementation()
{
	UE_LOG(XXXXX_Log_QG, Warning, TEXT("@@@@@ [%s] Interact_Implementation() called from base AQG_Interactable Class but should not"), *this->GetName());
}


