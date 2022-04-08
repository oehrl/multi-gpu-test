// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiGPUWindowTest.h"


// Sets default values
AMultiGPUWindowTest::AMultiGPUWindowTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMultiGPUWindowTest::BeginPlay()
{
	Super::BeginPlay();

  //Initialize GameInstance of new viewport client
  GameInstance = NewObject<UMultiGPUGameInstance>(GEngine, UMultiGPUGameInstance::StaticClass());
  // GameInstance ->InitializeExtraWindowUIContext(GetWorld()->GetFirstPlayerController());

  //Initialize Viewport Client
  ViewportClient = NewObject<UGameViewportClient>(GEngine, UGameViewportClient::StaticClass()); 
  ViewportClient ->Init(*GameInstance->GetWorldContext(), GameInstance, false);

  GameInstance->GetWorldContext()->GameViewport = ViewportClient;
	
  Window = SNew(SWindow)
      .Type(EWindowType::Normal)
      .FocusWhenFirstShown(true)
      .ClientSize(FVector2D(640, 480))
      .ActivationPolicy(EWindowActivationPolicy::Never);
  FSlateApplication::Get().AddWindow(Window.ToSharedRef(), true);

  // Attach the viewport client to a new viewport.
	TSharedRef<SOverlay> ViewportOverlayWidgetRef = SNew(SOverlay);
	ViewportOverlayWidgetRef->SetCursor(EMouseCursor::Default);

  TSharedRef<SGameLayerManager> LayerManagerRef = SNew(SGameLayerManager)
    .SceneViewport(ViewportClient->GetGameViewport())
    .Visibility(EVisibility::Visible)
    .UseScissor(true)
    [
      ViewportOverlayWidgetRef
    ];

  Viewport = SNew(SViewport)
    .RenderDirectlyToWindow(true)
    .EnableGammaCorrection(false)
    .EnableStereoRendering(false);

  ViewportClient->SetViewportOverlayWidget(Window, ViewportOverlayWidgetRef);
  ViewportClient->SetGameLayerManager(LayerManagerRef);

  ExtraWindowSceneViewport = MakeShareable(new FSceneViewport(ExtraWindowViewportClient, Viewport));
  ViewportClient->Viewport = ExtraWindowSceneViewport.Get();
  Viewport->SetViewportInterface(ExtraWindowSceneViewport.ToSharedRef());

  FViewportFrame* ViewportFrame = ExtraWindowSceneViewport.Get();
  ViewportClient->SetViewportFrame(ViewportFrame);

  Window->SetContent(Viewport.ToSharedRef());

  TSharedPtr<SWidget> UserSlateWidget = TakeWidget();
  TSharedRef<SConstraintCanvas> ViewportWidget = SNew(SConstraintCanvas);
  ViewportWidget->AddSlot()
    .Offset(BIND_UOBJECT_ATTRIBUTE(FMargin, GetFullScreenOffset))
    .Anchors(BIND_UOBJECT_ATTRIBUTE(FAnchors, GetViewportAnchors))
    .Alignment(BIND_UOBJECT_ATTRIBUTE(FVector2D, GetFullScreenAlignment))
    [
      UserSlateWidget.ToSharedRef()
    ];
  ExtraWindowViewportClient->AddViewportWidgetContent(ViewportWidget, 10);

	Window->SetContent(Viewport.ToSharedRef());
}

void AMultiGPUWindowTest::EndPlay(EEndPlayReason::Type Reason) {
  Super::EndPlay(Reason);
  Window->RequestDestroyWindow();
}

// Called every frame
void AMultiGPUWindowTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

