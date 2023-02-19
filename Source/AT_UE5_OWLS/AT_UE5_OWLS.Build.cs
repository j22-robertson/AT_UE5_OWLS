// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AT_UE5_OWLS : ModuleRules
{
	public AT_UE5_OWLS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
