// Peter Kmiecik Art All Rights Reserved


#include "QAUserWidget.h"
#include "Components/Button.h"
#include "Components/Widget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/SlateCore/Public/Input/Reply.h"

 void UQAUserWidget::GetAllButtonWidgets(TArray< UButton*> & Array)
{

	// TO DO Clear this code
	UWidgetTree* WidgetTreeToGet = UQAUserWidget::WidgetTree;
		//UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: name of widgettree: %s       %s \n"), *WidgetTreeToGet->GetName(), *WidgetTreeToGet->GetClass()->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: name of rootwidget: %s \n"), *WidgetTreeToGet->RootWidget->GetName());
	WidgetTreeToGet->RootWidget->bCanChildrenBeAccessible = 1;

	TArray<UWidget*> Widgets;
	WidgetTreeToGet->GetAllWidgets(Widgets);
		//UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: number of widgets %i \n"), Widgets.Num()); // daje 12, 

		//TODO Sprawdziæ, co daj¹ te widgety których jest wiecej 23 
		/*WidgetTreeToGet->GetChildWidgets(WidgetTreeToGet->RootWidget, Widgets);
			UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: number of widgets %i \n"), Widgets.Num());*/
	
		if (Widgets.IsValidIndex(1))
		{
			for (int32 Index = 0; Index != Widgets.Num(); ++Index)
			{
			//	UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: number of widgets %s \n"), *Widgets.Last(Index)->GetName());
			}

			for (int32 Index = 0; Index != Widgets.Num(); ++Index)
			{
				UButton* button = Cast<UButton>(Widgets.Last(Index));

				if (button->IsValidLowLevel())
				{
					Array.Add(button);

					//UE_LOG(LogTemp, Warning, TEXT("GetAllButtonWidgets: number of buttons %f \n"), Array.Num());
				}
				else
				{
					//UE_LOG(LogTemp, Warning, TEXT("failed 		if (button)"));
				}
			}
		
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("failed 		if (Widgets.IsValidIndex(1))"));
		}
	
}

 //void UQAUserWidget::RespondToOnButtonFocus(bool Question)
 //{
 //}



 FReply UQAUserWidget::NativeOnFocusReceived(const FGeometry & InGeometry, const FFocusEvent & InFocusEvent)
 {


	  /* TODO aktualnie nie dzia³a. 
	  dzia³a event: OnButtonGainedFocus ale nic nie robi a powinien:

	  when key is focussed change its color
	  override the onfocusreceived function and expose it to bps with event (bind to event)
	  */

	// OnButtonFocus.Broadcast(true);
	 //UE_LOG(LogTemp, Warning, TEXT("NativeOnFocusReceived fired"));

	 
	 OnButtonGainedFocus();

	 return   FReply::Unhandled();
 }
 

