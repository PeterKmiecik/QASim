// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPS_InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class ARPS_InGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	ARPS_InGameHUD();

	virtual void DrawHUD() override;


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	
	UFUNCTION(BlueprintCallable, Category = "@@@ RPS HUD")
	 void UpdateCombatCount(int32 Value) ;
	
	UFUNCTION(BlueprintCallable, Category = "@@@ RPS HUD")
	void ResetCombo() ;

	UPROPERTY(EditAnywhere, Category = "@@@ RPS HUD")
	TSubclassOf < class UUserWidget > ComboWidgetClass;

private:
	class URPS_UserWidget* ComboWidget;
};
