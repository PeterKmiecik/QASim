// Fill out your copyright notice in the Description page of Project Settings.


#include "RPS_UserWidget.h"
#include "Runtime\UMG\Public\UMG.h"
#include "TextBlock.h"

URPS_UserWidget::URPS_UserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void URPS_UserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URPS_UserWidget::UpdateComboCount(int32 Value)
{
	if (TXTCombo && Value >= 1)
	{
		if (TXTCombo->Visibility == ESlateVisibility::Hidden)
		{
			TXTCombo->SetVisibility(ESlateVisibility::Visible);
		}
		TXTCombo->SetText(FText::FromString(FString::FromInt(Value) + "x Combo"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("@@@@@ [%s] UpdateComboCount() refs empty"), *this->GetName());
	}
}

void URPS_UserWidget::ResetCombo()
{
	if (TXTCombo)
	{
		TXTCombo->SetVisibility(ESlateVisibility::Hidden);
	}
}

UWidgetAnimation* URPS_UserWidget::GetAnimationByName(FName AnimationName) const
{
	return nullptr;


}

void URPS_UserWidget::StoreWidgetAnimations()
{
	//AnimationsMap.Empty();

	UProperty* Prop = GetClass()->PropertyLink;
	if (Prop->GetClass() == UObjectProperty::StaticClass())
	{
		UObjectProperty* ObjProp = Cast<UObjectProperty>(Prop);
		if (true)
		{

		}
	}
}
