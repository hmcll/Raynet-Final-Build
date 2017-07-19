// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "EnumsAndStructs.h"
#include "Raynet_PlayerController.generated.h"

/**
 *
 */
UCLASS()
class RAYNET_FINALBUILD_API ARaynet_PlayerController: public APlayerController {
	GENERATED_BODY()

public:
	ARaynet_PlayerController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Room")
		ARoom* roomin;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Room")
		int32 playerid;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Room")
		void startAsHost(bool offensive);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Room")
		void joinRoom(int32 RoomID);

	UFUNCTION(BlueprintCallable, Category = "Room")
		ARoom* getRoom();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "GamePlay")
		void addMove(FMove move);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "GamePlay")
		void changeStage(EGameStage inStage);

};

