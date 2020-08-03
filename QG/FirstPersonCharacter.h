#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

UCLASS()
class QG_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFirstPersonCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@@@ QG|First Person Character|Inventory")
	FString HelpText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "@@@ QG|First Person Character")
	int32 Gold;

	UFUNCTION(BlueprintCallable, Category = "@@@ QG|First Person Character|Inventory")
	void UpdateGold(int32 Amount);

	UFUNCTION(BlueprintPure, Category = "@@@ QG|First Person Character|Inventory")
	bool AddItemToInventory(class AQG_Pickup* Item);

	UFUNCTION(BlueprintPure, Category = "@@@ QG|First Person Character|Inventory")
	class UTexture2D * GetThumbnailAtInventorySlot(int32 Slot);

	/* //Gets item name for given invetory slot */
	UFUNCTION(BlueprintPure, Category = "@@@ QG|First Person Character|Inventory")
	FString GetItemNameAtInventorySlot(int32 Slot);

	UFUNCTION(BlueprintCallable, Category = "@@@ QG|First Person Character|Inventory")
	void UseItemAtInventorySlot(int32 Slot);

	/* // Actual player inventory container*/
	UPROPERTY(EditAnywhere, Category = "@@@ QG|First Person Character|Inventory")
	TArray<AQG_Pickup* > Inventory;

	UFUNCTION(BlueprintCallable, Category = "@@@ QG|First Person Character")
	FORCEINLINE	class UGrabber* GetGrabber()const { return Grabber; };

	UFUNCTION(BlueprintCallable, Category = "@@@ QG|First Person Character")
	FORCEINLINE	class UPhysicsHandleComponent* GetPhysicsHandleComponent()const { return PhysicsHandle; };
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Forward(float AxisValue);
	void Right(float AxisValue);
	void Grab();
	void Release();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|First Person Character")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|First Person Character")
	UGrabber* Grabber;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|First Person Character")
	UPhysicsHandleComponent* PhysicsHandle;

	class AQG_Interactable* CurrentInteractable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|First Person Character")
	float Reach;

	void ToggleInventoryOn();
	/* stub function*/
	void ToggleInventoryOff();
	/* // Interact with Interactable, provided theres one*/
	void Interact();

	/* //Checks for Interactable items directly in front of a player, called on tick basis */
	void CheckForInteractables();

	void CacheGameMode();
	class AQG_GameModeBase* AQG_GameMode;

	bool bToggleInventoryActive = false;
};
