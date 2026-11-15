using UnrealBuildTool;

public class UnrealEquipmentRoomTarget : TargetRules
{
    public UnrealEquipmentRoomTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("UnrealEquipmentRoom");
    }
}
