using UnrealBuildTool;
using System.Collections.Generic;

public class BoxteroidsEditorTarget : TargetRules
{
	public BoxteroidsEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;
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
