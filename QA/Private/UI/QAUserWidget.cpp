// Peter Kmiecik Art All Rights Reserved


#include "QAUserWidget.h"
#include "Components/Button.h"
#include "Components/Widget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/SlateCore/Public/Input/Reply.h"

 void UQAUserWidget::GetAllButtonWidgets(TArray< UButton*> & Array)
{   // //  TO DO DEMO: Clear this code

	UWidgetTree* WidgetTreeToGet = UQAUserWidget::WidgetTree;
	//WidgetTreeToGet->RootWidget->bCanChildrenBeAccessible = 1;

	TArray<UWidget*> Widgets;
	WidgetTreeToGet->GetAllWidgets(Widgets);
		//UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: number of widgets %i \n"), Widgets.Num()); // returns 12

		/*WidgetTreeToGet->GetChildWidgets(WidgetTreeToGet->RootWidget, Widgets);
		UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: number of widgets %i \n"), Widgets.Num());*/ 		//TODO check what does these ~23 do here, which ones are these

	
	if ( Widgets.IsValidIndex(1))
	{
		for (int32 Index = 0; Index != Widgets.Num(); ++Index)
		{
		//	UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: number of widgets %s \n"), *Widgets.Last(Index)->GetName());
		}

		for (int32 Index = 0; Index != Widgets.Num(); ++Index)
		{
			UButton* button = Cast<UButton>(Widgets.Last(Index));

			if ( button != NULL && button->IsValidLowLevel())
			{
				Array.Add(button);

				//UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: number of buttons %f \n"), Array.Num());
			}
			else
			{
				// TODO - this error is actually appearing, commented for clarity: 04.2020 
				//UE_LOG(LogTemp, Warning, TEXT("[%s] failed IsValidLowLevel (button)"),* this->GetName());
			}
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UserWidget: [%s] failed code: if (Widgets.IsValidIndex(1)) which checks if any button widget was added to array of all Widgets"), *this->GetName());
	}
	
}

 //void UQAUserWidget::RespondToOnButtonFocus(bool Question)
 //{
 //}

// // Returns color which was present at creation of parent user widget overlay
 FLinearColor UQAUserWidget::GetFirstButtonOriginalColor(TArray<class UButton*> Array)
 {
	 if (Array.Num() > 0)
	 {
		UButton** PtrButton =  Array.GetData();
		UButton* Button = *PtrButton;
		if (Button)
		{
			OriginalButtonColor =  Button->ColorAndOpacity;
		}
	 }
	 else
	 {
		 UE_LOG(LogTemp, Error, TEXT("UserWidget: %s Array passed to GetFirstButtonOriginalColor is empty !"), *this->GetName());

	 }
		 return OriginalButtonColor;
 }

 FReply UQAUserWidget::NativeOnFocusReceived(const FGeometry & InGeometry, const FFocusEvent & InFocusEvent)
 {
	  /* TODO not working currently
	  event: OnButtonGainedFocus but it does't do antything, should :

	  when key is focussed change its color
	  override the onfocusreceived function and expose it to bps with event (bind to event)
	  */
	
	 OnButtonGainedFocus();

	 return   FReply::Unhandled();
 }
 

