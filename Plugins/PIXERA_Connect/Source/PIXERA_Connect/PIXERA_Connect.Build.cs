// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class PIXERA_Connect : ModuleRules
{
	public PIXERA_Connect(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseRTTI = true;
		bPrecompile = true;
		PrecompileForTargets = PrecompileTargetsType.Any;
        bUsePrecompiled = true;
		bEnableExceptions = true;

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}

			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
            }
				
				
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"RenderCore",
				"EngineSettings",
				"DisplayClusterConfiguration",
				"DisplayCluster",
				"CinematicCamera",
				"AssetRegistry"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate",
				"SlateCore",
				"InputCore",
				"Networking",
				"Sockets",
				"JsonUtilities",
				"Json",
				"DisplayCluster",
				"Json",
				"JsonUtilities",
				"AssetRegistry"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        PublicDefinitions.AddRange(
            new string[]
            {
                "IS_UNREAL=1"
            }
            );
    }
}
