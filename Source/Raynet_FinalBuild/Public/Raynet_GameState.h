// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "EnumsAndStructs.h"
#include "Room.h"
#include "Raynet_GameState.generated.h"

/**
 * 
 */
UCLASS()
class RAYNET_FINALBUILD_API ARaynet_GameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(Replicated)
		TArray<ARoom*> Rooms;

	
};
