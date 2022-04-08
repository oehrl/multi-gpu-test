// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MultiGPUTestHUD.generated.h"

UCLASS()
class AMultiGPUTestHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMultiGPUTestHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

