using UnrealBuildTool;
using System.Collections.Generic;

public class BoxteroidsTarget : TargetRules
{
	public BoxteroidsTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.Add("Boxteroids");
	}
}
