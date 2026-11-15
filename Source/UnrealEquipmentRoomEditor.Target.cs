using UnrealBuildTool;

public class UnrealEquipmentRoomEditorTarget : TargetRules
{
    public UnrealEquipmentRoomEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("UnrealEquipmentRoom");
    }
}
