// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BT_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UBT_UserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UPROPERTY(meta = (BindWidget))
	//class UCanvasPanel* Panel;
	//UPROPERTY(meta = (BindWidget))
	//class UImage* AimPoint;
	//UPROPERTY(meta = (BindWidget))
	//class UTextBlock* AmmoText;

	void Setup();
};
