#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"
#include "EquipmentRoomGameMode.generated.h"

class AStaticMeshActor;
class UStaticMesh;

UCLASS()
class AEquipmentRoomGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AEquipmentRoomGameMode();
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual void StartPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    void Cycle();
    void ResetDemonstration();
    FString GetStatus() const;

private:
    AStaticMeshActor* AddBox(
        const FVector& Center, const FVector& Size, const FLinearColor& Color,
        bool bSolid = true, bool bMovable = false);

    UPROPERTY()
    TObjectPtr<UStaticMesh> Cube;

    UPROPERTY()
    TObjectPtr<AStaticMeshActor> Module;

    UPROPERTY()
    TObjectPtr<AStaticMeshActor> Bezel;

    float Progress = 0.0f;
    float Destination = 0.0f;
};

UCLASS()
class AEquipmentRoomController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;

private:
    void CycleEquipment();
    void ResetEquipment();
};

UCLASS()
class AEquipmentRoomHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;
};
