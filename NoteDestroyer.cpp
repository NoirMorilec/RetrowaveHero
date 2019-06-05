// Fill out your copyright notice in the Description page of Project Settings.

#include "NoteDestroyer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "SingleNote.h"
#include "Kismet/GameplayStatics.h"
#include "DefaultMusicPawn.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#define print(str) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::FString(str));

// Sets default values
ANoteDestroyer::ANoteDestroyer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("NewRoot"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NewMesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("NewBox"));
	RootComponent = Root;
	Mesh->SetupAttachment(Root);
	Box->SetupAttachment(Root);

	if (Box)
	{
		Box->OnInputTouchBegin.AddDynamic(this, &ANoteDestroyer::OnClickStart);
	}
	PickupPSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PickupFX"));
	PickupPSC->bAutoActivate = false;
	PickupPSC->bAutoDestroy = false;
	PickupPSC->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANoteDestroyer::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstanceDynamic*  DynMat = Mesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMat)
	{
		DynMat->SetVectorParameterValue("Color", OnRelease);
	}

	Player = Cast<ADefaultMusicPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		EffectDelay = Player->GetEffectDelay();
	}
}

/*void ANoteDestroyer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}*/


void ANoteDestroyer::OnClickStart(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	TArray<AActor*> ActorsArray;
	Box->GetOverlappingActors(ActorsArray);
	if (ActorsArray.Num())
	{
		ASingleNote* tmp = Cast<ASingleNote>(ActorsArray[0]);
		if (tmp)
		{
			tmp->Destroy();
			if (Player)
			{
				uint16 CurrentScore = Player->GetScore();
				CurrentScore += 10;
				Player->SetScore(CurrentScore);

				if (ActiveFX)
				{
					PickupPSC->SetTemplate(ActiveFX);
					PickupPSC->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));
					PickupPSC->ActivateSystem();
				}
			}
		}
	}
	
	UMaterialInstanceDynamic*  DynMat = Mesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMat)
	{
		DynMat->SetVectorParameterValue("Color", OnTap);
	}
	GetWorldTimerManager().SetTimer(Timer, this, &ANoteDestroyer::OnClickEnd, EffectDelay);
}

void ANoteDestroyer::OnClickEnd()
{
	UMaterialInstanceDynamic*  DynMat = Mesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMat)
	{
		DynMat->SetVectorParameterValue("Color", OnRelease);
	}

	GetWorldTimerManager().ClearTimer(Timer);
}

