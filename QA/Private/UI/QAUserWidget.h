// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QAUserWidget.generated.h"

/**
 * Base Widget class with autoatic button highlight and keyboard selection
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewSth, bool, question);

UCLASS()
class UQAUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/* // PROTO: working */
	UFUNCTION(BlueprintCallable, Category = "@@@ QAUserWidget")
	void GetAllButtonWidgets(TArray<class UButton*> & Array);

	/* // Event to avoid ticking and for loops for active button check */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnButtonGainedFocus();

	/** // Returns color which was present at creation of parent user widget overlay  */
	UFUNCTION(BlueprintCallable, Category = "@@@ QAUserWidget")
	FLinearColor GetFirstButtonOriginalColor(TArray<class UButton*> Array);

	/*
	//DECLARE_EVENT(FEventType, eventname);
	//FReply On
	
	UPROPERTY(BlueprintAssignable)
	FNewSth OnButtonFocus;

	UFUNCTION(BlueprintCallable)
	void RespondToOnButtonFocus(bool Question);
	*/

	/* // Overrided native function to add event in BPs for active buttons */
	virtual  FReply NativeOnFocusReceived( const FGeometry& InGeometry, const FFocusEvent& InFocusEvent ) override;

	UPROPERTY(BlueprintReadWrite, Category = "@@@ QAUserWidget")
	/** //Button color which wa present at creation of this button */
	FLinearColor OriginalButtonColor;
};
