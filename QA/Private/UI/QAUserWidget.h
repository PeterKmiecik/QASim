// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QAUserWidget.generated.h"

/**
 * 
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewSth, bool, question);

UCLASS()
class UQAUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/* // Initial Setup function Exposed to BPs  */
	UFUNCTION(BlueprintCallable)
	void GetAllButtonWidgets(TArray<class UButton*> & Array);

	/* // Event to avoid ticking and for loops for active button check */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnButtonGainedFocus();

	/*
	//DECLARE_EVENT(FEventType, eventname);
	//FReply On
	
	UPROPERTY(BlueprintAssignable)
	FNewSth OnButtonFocus;

	UFUNCTION(BlueprintCallable)
	void RespondToOnButtonFocus(bool Question);
	*/

	/* // Overrided native class to add event in BPs for active buttons */
	virtual  FReply NativeOnFocusReceived( const FGeometry& InGeometry, const FFocusEvent& InFocusEvent ) override;
};
