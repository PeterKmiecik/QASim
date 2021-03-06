// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BattleTank : ModuleRules
{
    public BattleTank(ReadOnlyTargetRules Target) : base (Target)
	{
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "UMG" , "NavigationSystem", "QA"});

		PublicIncludePaths.AddRange(new string[] {"BattleTank/Public"});
		
		PrivateIncludePaths.AddRange(new string[] {"BattleTank/Private"});
		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }
	}
}
