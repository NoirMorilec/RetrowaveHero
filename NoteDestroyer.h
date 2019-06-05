// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteDestroyer.generated.h"

UCLASS()
class RETROWAVEHERO_API ANoteDestroyer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoteDestroyer();

private:

	/** FX component */
	UPROPERTY(VisibleDefaultsOnly, Category = "Effects")
		class UParticleSystemComponent* PickupPSC;

protected:
	/** FX of active pickup */
	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* ActiveFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box;

	FTimerHandle Timer;

	class ADefaultMusicPawn* Player;

	UPROPERTY(VisibleAnywhere)
		float EffectDelay;

	UPROPERTY(EditAnywhere)
	FLinearColor OnTap;
	UPROPERTY(EditAnywhere)
	FLinearColor OnRelease;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OnClickStart(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void OnClickEnd();
};
