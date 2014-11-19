using UnrealBuildTool;

public class Boxteroids : ModuleRules
{
	public Boxteroids(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(
            new string[] 
            { 
                "Core", 
                "CoreUObject", 
                "Engine", 
                "InputCore" 
            }
        );
	}
}
