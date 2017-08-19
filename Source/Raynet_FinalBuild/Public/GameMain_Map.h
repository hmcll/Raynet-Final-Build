// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "GameMain_Map.generated.h"

/**
 * 
 */
UCLASS()
class RAYNET_FINALBUILD_API AGameMain_Map : public ALevelScriptActor
{
	GENERATED_BODY ()
public:

	void BeginPlay () override;

	
	UFUNCTION ( BlueprintImplementableEvent )
		void AfterBeginPlay ();
};
