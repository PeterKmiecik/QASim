// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class RPS : ModuleRules
{
	public RPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "QA" });

		PrivateDependencyModuleNames.AddRange(new string[] { "QA" });

        PublicIncludePaths.AddRange(new string[] { "RPS/Public" });

        PrivateIncludePaths.AddRange(new string[] { "RPS/Private" });

        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
