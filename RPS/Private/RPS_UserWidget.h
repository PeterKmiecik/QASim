// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPS_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class URPS_UserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	URPS_UserWidget(const FObjectInitializer& ObjectInitializer);



protected:
	virtual void NativeConstruct() override;
private:

};
