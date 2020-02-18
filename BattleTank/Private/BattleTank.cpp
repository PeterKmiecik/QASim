// Fill out your copyright notice in the Description page of Project Settings.

//#include "ModuleManager.h"

#include "BattleTank.h"

void FBattleTank::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Orfeas module has started!"));
}

void FBattleTank::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Orfeas module has shut down"));
}

IMPLEMENT_GAME_MODULE(FDefaultModuleImpl, BattleTank);

//#include "BattleTank.h"

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, BattleTank, "BattleTank" );
