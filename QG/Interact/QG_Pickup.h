#pragma once

#include "CoreMinimal.h"
#include "Interact/QG_Interactable.h"
#include "QG_Pickup.generated.h"

UCLASS()
class QG_API AQG_Pickup : public AQG_Interactable
{
	GENERATED_BODY()

public:
	AQG_Pickup();
	
	void OnPickedUp();
	
	UFUNCTION(BlueprintNativeEvent, Category = "@@@ QG|AQG_Pickup")
	void Use();

	FORCEINLINE class UTexture2D* GetPickupThumbnail() { return PickupThumbnail; };
	FORCEINLINE FString GetItemName() { return ItemName; };
	/* // Override it in child classes for custom interaction when clicked on in inventory*/
	virtual void  Use_Implementation();
protected:
	virtual void Interact_Implementation() override;
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "@@@ QG|AQG_Pickup")
	int32 Value;

	UPROPERTY(EditAnywhere, Category = "@@@ QG|AQG_Pickup")
	FString ItemName;

	UPROPERTY(EditAnywhere, Category = "@@@ QG|AQG_Pickup")
	 UTexture2D* PickupThumbnail;
	
};
