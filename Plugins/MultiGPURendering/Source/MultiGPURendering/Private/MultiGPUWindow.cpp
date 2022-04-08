// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiGPUWindow.h"


// Sets default values
AMultiGPUWindow::AMultiGPUWindow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMultiGPUWindow::BeginPlay()
{
	Super::BeginPlay();
  UE_LOG(LogTemp, Log, TEXT("Test before window"));
  auto Window = SNew(SWindow)
      .Type(EWindowType::Normal)
      .FocusWhenFirstShown(true)
      .ClientSize(FVector2D(640, 480))
      .ActivationPolicy(EWindowActivationPolicy::Never);

  FSlateApplication::Get().AddWindow(Window, true);
  UE_LOG(LogTemp, Log, TEXT("Test test test tes"));
  // Window.Pin()->Resize();
  // Window.Pin()->ShowWindow();
}

// Called every frame
void AMultiGPUWindow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

