using UnrealBuildTool;

public class Boxteroids : ModuleRules
{
    public Boxteroids(TargetInfo Target)
    {
        PrivateIncludePaths.Add("Boxteroids/Private");

        PublicDependencyModuleNames.AddRange(
            new string[] 
            { 
                "Core", 
                "CoreUObject", 
                "Engine", 
                "InputCore",
                "SlateCore",
                "Slate",
                "UMG"
            }
        );
    }
}
