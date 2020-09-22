// Peter Kmiecik Art All Rights Reserved

#include "RPS_ComboWidget.h"

#include "Runtime\UMG\Public\UMG.h"
#include "TextBlock.h"


void URPS_ComboWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URPS_ComboWidget::UpdateComboCount(int32 Value)
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

void URPS_ComboWidget::ResetCombo()
{
	if (TXTCombo)
	{
		TXTCombo->SetVisibility(ESlateVisibility::Hidden);
	}
}

UWidgetAnimation* URPS_ComboWidget::GetAnimationByName(FName AnimationName) const
{
	return nullptr;
}

void URPS_ComboWidget::StoreWidgetAnimations()
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
