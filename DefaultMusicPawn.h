// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DefaultMusicPawn.generated.h"

UCLASS()
class RETROWAVEHERO_API ADefaultMusicPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADefaultMusicPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Configs")
	uint16 Score;
	UPROPERTY(EditAnywhere, Category = "Configs")
	float NoteSpeed;

	UPROPERTY(EditAnywhere, Category = "Configs")
	class USoundCue* StartupCue;
	UPROPERTY(BlueprintReadOnly, Category = "Configs")
	class UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, Category = "Configs")
		float EffectDelay;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE float GetSpeed() const { return NoteSpeed; }
	UFUNCTION(BlueprintCallable)
	int GetScore() const { return Score; }
	FORCEINLINE float GetEffectDelay() const { return EffectDelay; }

	FORCEINLINE void SetScore(uint16 NewScore) { this->Score = NewScore; }

	void PlayMusic();
	bool IsMusicPlaying();
	bool bIsGameStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wMainMenu;
protected:
	// Variable to hold the widget After Creating it.
	UPROPERTY(EditAnywhere)
	UUserWidget* MyMainMenu;


	/*UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);*/
};
