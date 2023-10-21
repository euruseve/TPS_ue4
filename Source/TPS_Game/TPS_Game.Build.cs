// Third Person Shooter. All Rights Reserved. 

using UnrealBuildTool;

public class TPS_Game : ModuleRules
{
    public TPS_Game(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[]
        { "TPS_Game/Public/Player",
          "TPS_Game/Public/Components",
          "TPS_Game/Public/Dev",
          "TPS_Game/Public/Weapon",
          "TPS_Game/Public/UI",
          "TPS_Game/Public/Animations"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
