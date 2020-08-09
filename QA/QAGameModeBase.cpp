// Fill out your copyright notice in the Description page of Project Settings.


#include "QAGameModeBase.h"


AQAGameModeBase::AQAGameModeBase()
{
	// Suppress blue messages like Pause when transitioning
	if ((GEngine != NULL) && (GEngine->GameViewport != NULL))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}
}

