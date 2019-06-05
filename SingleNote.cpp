// Fill out your copyright notice in the Description page of Project Settings.

#include "SingleNote.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultMusicPawn.h"
#define print(str) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::FString(str));

// Sets default values
ASingleNote::ASingleNote()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Root;
	Mesh->SetupAttachment(Root);
	speed = 0;

}

// Called when the game starts or when spawned
void ASingleNote::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ADefaultMusicPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		speed = Player->GetSpeed();
	}
}

// Called every frame
void ASingleNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	FVector NewLocation = GetActorLocation();
	NewLocation.X -= DeltaTime ? speed * DeltaTime : speed;
	SetActorLocation(NewLocation);

	if (Player &&  NewLocation.X < 182 && !Player->IsMusicPlaying())
	{
		Player->PlayMusic();
	}
	if (Player && NewLocation.X < 100)
	{
		uint16 CurrentScore = Player->GetScore();
		if (CurrentScore >= 10)
		{
			CurrentScore -= 10;
			Player->SetScore(CurrentScore);
		}
		else
		{
			Player->SetScore(0);
		}

		Destroy();
	}
}

void ASingleNote::SetSpeed(float speed)
{
	this->speed = speed;
}
