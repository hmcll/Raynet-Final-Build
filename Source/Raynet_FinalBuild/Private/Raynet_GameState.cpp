// Fill out your copyright notice in the Description page of Project Settings.

#include "Raynet_FinalBuild.h"
#include "Net/UnrealNetwork.h"
#include "Raynet_GameState.h"





void ARaynet_GameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaynet_GameState, Rooms);
}