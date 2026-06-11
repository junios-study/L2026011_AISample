// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AISample : ModuleRules
{
	public AISample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"AISample",
			"AISample/Variant_Platforming",
			"AISample/Variant_Platforming/Animation",
			"AISample/Variant_Combat",
			"AISample/Variant_Combat/AI",
			"AISample/Variant_Combat/Animation",
			"AISample/Variant_Combat/Gameplay",
			"AISample/Variant_Combat/Interfaces",
			"AISample/Variant_Combat/UI",
			"AISample/Variant_SideScrolling",
			"AISample/Variant_SideScrolling/AI",
			"AISample/Variant_SideScrolling/Gameplay",
			"AISample/Variant_SideScrolling/Interfaces",
			"AISample/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
