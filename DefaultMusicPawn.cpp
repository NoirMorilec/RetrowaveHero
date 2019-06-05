// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultMusicPawn.h"
#include "Camera/CameraComponent.h"
#include "SingleNote.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#define print(str) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::FString(str));

// Sets default values
ADefaultMusicPawn::ADefaultMusicPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	RootComponent = Root;
	Camera->SetupAttachment(Root);
	AudioComponent->SetupAttachment(RootComponent);

	Score = NoteSpeed = EffectDelay = 0;

	bIsGameStarted = false;
	/*
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("NewBox"));
	Box->SetupAttachment(Root);
	if (Box)
	{
		Box->OnComponentBeginOverlap.AddDynamic(this, &ADefaultMusicPawn::OnOverlap);
	}
	*/
}

// Called when the game starts or when spawned
void ADefaultMusicPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADefaultMusicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsGameStarted && !IsMusicPlaying())
	{
		if (wMainMenu) // Check if the Asset is assigned in the blueprint.
		{
			// Create the widget and store it.
			APlayerController* Controller = Cast<APlayerController>(GetController());
			if (Controller)
			{
				MyMainMenu = CreateWidget<UUserWidget>(Controller, wMainMenu);

				// now you can use the widget directly since you have a referance for it.
				// Extra check to  make sure the pointer holds the widget.
				if (MyMainMenu)
				{
					//let add it to the view port
					MyMainMenu->AddToViewport();
				}
			}
			
		}
		bIsGameStarted = false;
	}
}

// Called to bind functionality to input
void ADefaultMusicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADefaultMusicPawn::PlayMusic()
{
	if (StartupCue)
	{
		bIsGameStarted = true;
		AudioComponent->SetSound(StartupCue);
		AudioComponent->Play();
	}
}

bool ADefaultMusicPawn::IsMusicPlaying()
{
	return AudioComponent->IsPlaying();
}
