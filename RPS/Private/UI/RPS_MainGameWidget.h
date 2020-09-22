// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "RPS_UserWidget.h"
#include "UserWidget.h"
#include "RPS_GameMode.h"
#include "RPS_MainGameWidget.generated.h"

class UHorizontalBox;
class UImage;
class UTexture2D;
class UWidgetAnimation;

/**
 * Main game loop HUD display 
 */
UCLASS(BlueprintType, AutoExpandCategories = (RPS, MainGameWidget, Refs))
class URPS_MainGameWidget : public URPS_UserWidget
{
	GENERATED_BODY()
public:
	URPS_MainGameWidget(const FObjectInitializer& ObjectInitializer);
	UHorizontalBox* GetPlayerShapesButtonsBox() const ;
	UImage* GetPlayerHandImage();
	UImage* GetCpuHandImage();

	// TODO: Make RPS_GlobalDefines class with enums
	UTexture2D* GetPlayableShape2DTexture(EPlayableShape ShapeType);
	void PlayAttackAnimation(UWidgetAnimation*  InWidgetObjectAnimation);
	UWidgetAnimation* GetAttackAnimation();
protected:
	/** Overrided from UUserWidget*/
	virtual bool Initialize() override;


private:
	void Init();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"), Category = "@@@ RPS|MainGameWidget|Refs")
	UHorizontalBox* PlayerShapesButtonsBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"), Category = "@@@ RPS|MainGameWidget|Refs")
	UImage* PlayerHandImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"), Category = "@@@ RPS|MainGameWidget|Refs")
	UImage* CpuHandImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|MainGameWidget|Refs")
	UTexture2D* Scissors2DTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|MainGameWidget|Refs")
	UTexture2D* Rock2DTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|MainGameWidget|Refs")
	UTexture2D* Paper2DTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|MainGameWidget|Refs")
	UWidgetAnimation* AttackAnimation;


};
