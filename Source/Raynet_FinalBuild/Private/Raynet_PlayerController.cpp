// Fill out your copyright notice in the Description page of Project Settings.

#include "Raynet_FinalBuild.h"
#include "Raynet_FinalBuildGameModeBase.h"
#include "Room.h"
#include "Net/UnrealNetwork.h"
#include "Raynet_PlayerController.h"



void ARaynet_PlayerController::startAsHost_Implementation(bool offensive) {
	auto s = Cast<ARaynet_FinalBuildGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	s->createRoom(offensive,this);
	playerid = offensive?1:2;
}

bool ARaynet_PlayerController::startAsHost_Validate(bool offensive) {
	return true;
}

void ARaynet_PlayerController::joinRoom_Implementation(int32 RoomID) {
	auto s = Cast<ARaynet_FinalBuildGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	s->joinRoom(RoomID,this);
	playerid = roomin->Offensive ? 2 : 1;

}

bool ARaynet_PlayerController::joinRoom_Validate(int32 RoomID) {
	return true;
}

void ARaynet_PlayerController::addMove_Implementation(FMove move) {
	roomin->addMove(move);
}

bool ARaynet_PlayerController::addMove_Validate(FMove move) {
	return true;
}

ARoom* ARaynet_PlayerController::getRoom() {
	return roomin;
}

void ARaynet_PlayerController::changeStage_Implementation(EGameStage inStage) {
	roomin->RoomStage = inStage;
}

bool ARaynet_PlayerController::changeStage_Validate(EGameStage inStage) {
	return true;
}
ARaynet_PlayerController::ARaynet_PlayerController(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
}

void ARaynet_PlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaynet_PlayerController, roomin);
	DOREPLIFETIME(ARaynet_PlayerController, playerid);
}