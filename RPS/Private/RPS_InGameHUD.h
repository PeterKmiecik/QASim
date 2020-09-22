// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPS_InGameHUD.generated.h"

class URPS_UserWidget;
class URPS_MainGameWidget;
class URPS_ComboWidget;
class UUserWidget;
class URPS_TimerTexBlockWidget;
/**
 *  Main In Game HUD where RPS gameplay takes place
 */
UCLASS(BlueprintType, AutoExpandCategories = (XXXXXxRPS,RPS,HUD,Refs))
class ARPS_InGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	ARPS_InGameHUD();

	UFUNCTION(BlueprintCallable, Category = "XXXXxRPS|HUD")
	 void UpdateCombatCount(int32 Value);
	
	UFUNCTION(BlueprintCallable, Category = "@@@ RPS|HUD")
	void ResetCombo();

	FORCEINLINE URPS_ComboWidget* GetComboWidget() const { return ComboWidget; };
	FORCEINLINE URPS_MainGameWidget* GetMainGameWidget() const { return MainGameWidget; };
	FORCEINLINE URPS_TimerTexBlockWidget* GetTurnTimerWidget() const { return TurnTimerWidget; };

	void OpenMainMenu();
	void PlayMainGame();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	URPS_ComboWidget* ComboWidget;
	URPS_MainGameWidget* MainGameWidget;
	URPS_TimerTexBlockWidget* TurnTimerWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "XXXXxRPS|HUD")
	TSubclassOf < URPS_ComboWidget > ComboWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|HUD|Refs")
	TSubclassOf < URPS_MainGameWidget > MainGameWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|HUD|Refs")
	TSubclassOf < URPS_TimerTexBlockWidget > TurnTimerWidgetClass;

	void StopPlayingMainGame();

	void Init();
};
