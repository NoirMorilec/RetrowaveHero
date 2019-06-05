// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleNote.generated.h"

UCLASS()
class RETROWAVEHERO_API ASingleNote : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASingleNote();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	float speed;

	class ADefaultMusicPawn* Player;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetSpeed(float speed);
};
