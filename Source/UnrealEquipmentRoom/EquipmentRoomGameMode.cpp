#include "EquipmentRoomGameMode.h"

#include "Components/InputComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Canvas.h"
#include "Engine/PointLight.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/PlayerStart.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
    const FVector Staged(100.0, 0.0, 105.0);
    const FVector Seated(289.0, 0.0, 105.0);
    const FVector BezelOffset(-37.25, 0.0, 0.0);
    constexpr float CycleSeconds = 3.5f;
}

AEquipmentRoomGameMode::AEquipmentRoomGameMode()
{
    DefaultPawnClass = ADefaultPawn::StaticClass();
    PlayerControllerClass = AEquipmentRoomController::StaticClass();
    HUDClass = AEquipmentRoomHUD::StaticClass();
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(
        TEXT("/Engine/BasicShapes/Cube.Cube"));
    Cube = CubeAsset.Object;
}

void AEquipmentRoomGameMode::InitGame(
    const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
    GetWorld()->SpawnActor<APlayerStart>(FVector(-100, -160, 155), FRotator(-8, 25, 0));
}

void AEquipmentRoomGameMode::StartPlay()
{
    Super::StartPlay();

    const FLinearColor Floor(0.15f, 0.19f, 0.23f);
    const FLinearColor Wall(0.32f, 0.39f, 0.46f);
    const FLinearColor Cabinet(0.055f, 0.08f, 0.12f);
    const FLinearColor Rail(0.52f, 0.62f, 0.73f);
    const FLinearColor Orange(1.0f, 0.27f, 0.045f);
    const FLinearColor Teal(0.02f, 0.65f, 0.6f);

    AddBox(FVector(90, 0, -10), FVector(960, 740, 20), Floor);
    AddBox(FVector(570, 0, 155), FVector(16, 740, 310), Wall);
    AddBox(FVector(-390, 0, 155), FVector(16, 740, 310), Wall);
    AddBox(FVector(90, 370, 155), FVector(960, 16, 310), Wall);
    AddBox(FVector(90, -370, 155), FVector(960, 16, 310), Wall);
    AddBox(FVector(90, 0, 310), FVector(960, 740, 16), Wall);

    for (double Side : {-1.0, 1.0})
    {
        AddBox(FVector(290, Side * 31, 112), FVector(92, 4, 224), Cabinet);
        AddBox(FVector(287, Side * 23.2, 105), FVector(84, 2, 8.9), Rail);
    }
    AddBox(FVector(290, 0, 222), FVector(92, 66, 4), Cabinet);
    AddBox(FVector(290, 0, 3), FVector(92, 66, 6), Cabinet);
    AddBox(FVector(290, 0, 98.3), FVector(92, 56, 4.5), Cabinet);
    AddBox(FVector(290, 0, 111.7), FVector(92, 56, 4.5), Cabinet);
    AddBox(FVector(100, 0, 49.8), FVector(72, 62, 99.6), Cabinet);
    AddBox(FVector(100, 0, 100.175), FVector(78, 58, 1.15), Rail);

    AddBox(FVector(120, -105, 60), FVector(35, 40, 120), Cabinet);
    AddBox(FVector(106, -105, 117), FVector(12, 34, 20), Orange);
    AddBox(FVector(99, -105, 119), FVector(3, 20, 9), Teal);

    Module = AddBox(Staged, FVector(72, 44, 8.5), Teal, false, true);
    Bezel = AddBox(Staged + BezelOffset, FVector(2.5, 44, 8.5), Rail, false, true);

    for (const FVector& Position : { FVector(20, -125, 258), FVector(340, 10, 255) })
    {
        APointLight* Light = GetWorld()->SpawnActor<APointLight>(Position, FRotator::ZeroRotator);
        if (Light)
        {
            UPointLightComponent* Component = CastChecked<UPointLightComponent>(
                Light->GetLightComponent());
            Component->SetMobility(EComponentMobility::Movable);
            Component->SetIntensity(4200.0f);
            Component->SetAttenuationRadius(540.0f);
            Component->SetSourceRadius(24.0f);
        }
    }
}

AStaticMeshActor* AEquipmentRoomGameMode::AddBox(
    const FVector& Center, const FVector& Size, const FLinearColor& Color,
    bool bSolid, bool bMovable)
{
    if (!Cube)
    {
        return nullptr;
    }

    AStaticMeshActor* Box = GetWorld()->SpawnActor<AStaticMeshActor>(Center, FRotator::ZeroRotator);
    if (!Box)
    {
        return nullptr;
    }

    UStaticMeshComponent* Mesh = Box->GetStaticMeshComponent();
    Mesh->SetMobility(EComponentMobility::Movable);
    Mesh->SetStaticMesh(Cube);
    Mesh->SetWorldScale3D(Size / 100.0);
    if (UMaterialInstanceDynamic* Material = Mesh->CreateDynamicMaterialInstance(0))
    {
        Material->SetVectorParameterValue(TEXT("Color"), Color);
    }
    Mesh->SetCollisionProfileName(bSolid ? TEXT("BlockAll") : TEXT("NoCollision"));
    if (!bMovable)
    {
        Mesh->SetMobility(EComponentMobility::Static);
    }
    return Box;
}

void AEquipmentRoomGameMode::Cycle()
{
    if (Module && Bezel && Progress == Destination)
    {
        Destination = Destination == 0.0f ? 1.0f : 0.0f;
    }
}

void AEquipmentRoomGameMode::ResetDemonstration()
{
    Destination = 0.0f;
}

void AEquipmentRoomGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!Module || !Bezel || Progress == Destination)
    {
        return;
    }

    Progress = FMath::FInterpConstantTo(Progress, Destination, DeltaSeconds, 1.0f / CycleSeconds);
    const FVector Position = FMath::Lerp(Staged, Seated, FMath::SmoothStep(0.0f, 1.0f, Progress));
    Module->SetActorLocation(Position);
    Bezel->SetActorLocation(Position + BezelOffset);
}

FString AEquipmentRoomGameMode::GetStatus() const
{
    if (!Module || !Bezel)
    {
        return TEXT("Equipment mesh unavailable.");
    }
    if (Progress != Destination)
    {
        return Destination > Progress ? TEXT("Installing module") : TEXT("Removing module");
    }
    return Progress == 1.0f ? TEXT("Module seated") : TEXT("Module staged");
}

void AEquipmentRoomController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction(TEXT("CycleEquipment"), IE_Pressed, this,
        &AEquipmentRoomController::CycleEquipment);
    InputComponent->BindAction(TEXT("ResetEquipment"), IE_Pressed, this,
        &AEquipmentRoomController::ResetEquipment);
}

void AEquipmentRoomController::CycleEquipment()
{
    if (AEquipmentRoomGameMode* Mode = GetWorld()->GetAuthGameMode<AEquipmentRoomGameMode>())
    {
        Mode->Cycle();
    }
}

void AEquipmentRoomController::ResetEquipment()
{
    if (AEquipmentRoomGameMode* Mode = GetWorld()->GetAuthGameMode<AEquipmentRoomGameMode>())
    {
        Mode->ResetDemonstration();
    }
}

void AEquipmentRoomHUD::DrawHUD()
{
    Super::DrawHUD();
    if (const AEquipmentRoomGameMode* Mode = GetWorld()->GetAuthGameMode<AEquipmentRoomGameMode>())
    {
        DrawText(TEXT("Equipment Room"), FLinearColor::White, 24, 24, nullptr, 1.5f);
        DrawText(Mode->GetStatus(), FLinearColor::White, 24, 57);
        DrawText(TEXT("WASD + mouse: inspect   E: install / remove   R: return to staging"),
            FLinearColor::White, 24, 82);
    }
}
