// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiGPUTestGameMode.h"
#include "MultiGPUTestHUD.h"
#include "MultiGPUTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiGPUTestGameMode::AMultiGPUTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMultiGPUTestHUD::StaticClass();
}
