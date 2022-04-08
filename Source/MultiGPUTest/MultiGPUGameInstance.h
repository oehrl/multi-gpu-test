// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MultiGPUGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIGPUTEST_API UMultiGPUGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void Init();
};
