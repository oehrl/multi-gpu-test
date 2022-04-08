// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "Widgets/SViewport.h"
#include "GameFramework/Actor.h"
#include "MultiGPUGameInstance.h"
#include "Slate/SceneViewport.h"
#include "Blueprint/UserWidget.h"
#include "MultiGPUWindowTest.generated.h"

class MULTIGPUTEST_API FMultiGPUViewportClient : public FViewportClient {
public:
  virtual void Draw(FViewport* viewport, FCanvas* Canvas) override;
};

class MULTIGPUTEST_API SMultiGPUViewport : public SCompoundWidget
{
public:	
  SLATE_BEGIN_ARGS(SMultiGPUViewport) { }
	SLATE_END_ARGS()

public:
  void Construct(const FArguments& InArgs);

  // Called every frame
  virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
  TSharedPtr<SViewport> Viewport;
  TSharedPtr<FSceneViewport> SceneViewport;
  TSharedPtr<FMultiGPUViewportClient> ViewportClient;
};

UCLASS()
class MULTIGPUTEST_API AMultiGPUWindowTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiGPUWindowTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type Reason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
  // UMultiGPUGameInstance* GameInstance;
  // UGameViewportClient* ViewportClient;
  // UUserWidget* Widget;
  TSharedPtr<SMultiGPUViewport> Viewport;
  TSharedPtr<SWindow> Window;
};
