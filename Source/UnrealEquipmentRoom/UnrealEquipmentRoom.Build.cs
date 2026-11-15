using UnrealBuildTool;

public class UnrealEquipmentRoom : ModuleRules
{
    public UnrealEquipmentRoom(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore" });
    }
}
