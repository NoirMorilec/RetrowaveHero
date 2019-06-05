// Fill out your copyright notice in the Description page of Project Settings.

#include "NoteLine.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ANoteLine::ANoteLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	LineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LineMesh"));
	LineMesh->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void ANoteLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANoteLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

