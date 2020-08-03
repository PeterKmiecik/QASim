#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QG_Interactable.generated.h"

UCLASS()
class QG_API AQG_Interactable : public AActor
{
	GENERATED_BODY()
	
public:	
	AQG_Interactable();

protected:
	virtual void BeginPlay() override;
public:	

	void Interact();
	/* // Override it in child classes for custom interaction when E pressed*/
	virtual void Interact_Implementation();

	UPROPERTY(EditAnywhere, Category = "@@@ QG|QG_Interactable")
	class UStaticMeshComponent* InteractableMesh;
	
	UPROPERTY(EditAnywhere, Category = "@@@ QG|QG_Interactable")
	FString InteractableHelpText;

	bool bCanInteract = true;
	bool bCanBeGrabbed = true;
};
