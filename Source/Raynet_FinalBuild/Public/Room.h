// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnumsAndStructs.h"
#include "Room.generated.h"

#define TERMINAL_CARD_UNUSED true
#define TERMINAL_CARD_USED false

UCLASS()
class RAYNET_FINALBUILD_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly,Replicated)
		int32 RoomID;

	UPROPERTY(BlueprintReadOnly, Replicated)
		bool Offensive;

	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<FMove> MoveStack;

	UPROPERTY(BlueprintReadOnly, Replicated)
		EGameStage RoomStage;

	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<EPawn> Board;

	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<bool> Player1Terminal;

	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<bool> Player2Terminal;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 VC1;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 VC2;

	UPROPERTY(BlueprintReadOnly, Replicated)
		EPawn ServerShowingOff1;

	UPROPERTY(BlueprintReadOnly, Replicated)
		EPawn ServerShowingOff2;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 P1DBV;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 P1DBL;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 P2DBV;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 P2DBL;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 P1SEV;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 P1SEL;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 P2SEV;

	UPROPERTY(BlueprintReadOnly, Replicated)
		int32 P2SEL;

	FVector2D reverseVector(FVector2D in);

	int32 vectorToInt(FVector2D in);

	void addMove(FMove move);
	
	EPawn ToggleLineBoost(EPawn from);
};
