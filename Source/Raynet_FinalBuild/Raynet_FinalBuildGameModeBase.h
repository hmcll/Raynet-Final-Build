// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "EnumsAndStructs.h"
#include "Raynet_FinalBuildGameModeBase.generated.h"



/**
 *
 */
UCLASS()
class RAYNET_FINALBUILD_API ARaynet_FinalBuildGameModeBase: public AGameModeBase {
	GENERATED_BODY()

public:

	UPROPERTY(Replicated)
		int32 nextRoomId = 0;
	
	// Room Related
	UFUNCTION(Server, Reliable, WithValidation)
	void createRoom(bool offensive, APlayerController* PC);

	UFUNCTION(Server, Reliable, WithValidation)
	void joinRoom(int32 RoomID, APlayerController* PC);

	UFUNCTION(Server, Reliable, WithValidation)
	void deleteRoom(int32 RoomID);

	//gameLogic:
//	void SetPawn(FRoom* room, int32 playerID);

};
