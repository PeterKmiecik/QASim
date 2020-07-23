// Peter Kmiecik Art All Rights Reserved

#pragma once

// WIP https://www.youtube.com/watch?v=jeK6DPB5weA

#include "SlateBasics.h"
#include "SlateExtras.h"

class SMainMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainMenuWidget) {}
	SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, OwningHUD)
	SLATE_END_ARGS()

	/* every widget needs construction function*/
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AMenuHUD> OwningHUD;
};
