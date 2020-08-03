#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QG_GameModeBase.generated.h"

/* HUD state for active widget collection being shown */
UENUM(BlueprintType, Meta = (Bitflags))
enum class EHUDState : uint8
{
	HS_Ingame			UMETA(DisplayName = "DisplayName"),
	HS_Inventory		UMETA(DisplayName = "Inventory"),
	HS_Shop_General		UMETA(DisplayName = "Shop_General"),
	HS_Shop_Weapon		UMETA(DisplayName = "Shop_Weapon")
};

UCLASS()
class QG_API AQG_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AQG_GameModeBase();
	/* // Variable which is going to be exposed to BPs as dropdown list of EHUDState enum */
	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EHUDState"), Category = "@@@ QG|QG_GameModeBase|HUD")
	int32 HUDStateBitF;

	/* // spawns manager if it doesnt exist */
	UFUNCTION(BlueprintPure, Category = "@@@ QG|GameModeBase|Quests")
	FORCEINLINE	class AQuestManager* GetQuestManager() const { return QuestManager; }

	UFUNCTION(BlueprintPure, Category = "@@@ QG|GameModeBase|Quests")
	FORCEINLINE UClass* GetQuestManagerClass() const { return QuestManagerClass; }
	
	UFUNCTION(BlueprintCallable, Category = "@@@ QG|GameModeBase|Quests")
	void SetQuestManager(AQuestManager* InQuestManager) { QuestManager = InQuestManager; }

	FORCEINLINE EHUDState GetHUDState() { return HUDState; };

	FORCEINLINE void SetHUDState(EHUDState NewHUDState){HUDState = NewHUDState	;};

	/* // Setter for HUDState, applies new state and then calls applyHUDChanges */
	UFUNCTION(BlueprintCallable, Category = "@@@ QG|GameModeBase|HUD")
	void ChangeHUDState(EHUDState NewState);

	/* // Clears old widget and replaces it with new based on EHUDState */
	void ApplyHUDChanges();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	uint8 HUDStateVar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BlueprintProtected = "true", DisplayThumbnail = "true"), Category = "@@@ QG|QG_GameModeBase|HUD")
	TSubclassOf<UUserWidget> InGamHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BlueprintProtected = "true", DisplayThumbnail = "true"), Category = "@@@ QG|QG_GameModeBase|HUD")
	TSubclassOf<UUserWidget> InventoryHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BlueprintProtected = "true", DisplayThumbnail = "true"), Category = "@@@ QG|QG_GameModeBase|HUD")
	TSubclassOf<UUserWidget> ShopGeneralHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BlueprintProtected = "true", DisplayThumbnail = "true"), Category = "@@@ QG|QG_GameModeBase|HUD")
	UUserWidget* CurrentWidget;

	/* // Applies HUD to screen, returns true if successful, false otherwise */
	bool ApplyHUD(TSubclassOf<class UUserWidget>WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents, const FInputModeDataBase& InInputMode = FInputModeGameAndUI());
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|GameModeBase|Quests")
	UClass* QuestManagerClass;

	UPROPERTY()
	AQuestManager* QuestManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|QG_GameModeBase|HUD")
	EHUDState HUDState;

};