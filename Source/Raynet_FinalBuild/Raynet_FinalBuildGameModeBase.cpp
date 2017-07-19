// Fill out your copyright notice in the Description page of Project Settings.

#include "Raynet_FinalBuild.h"
#include "Raynet_GameState.h"
#include "Net/UnrealNetwork.h"
#include "Raynet_PlayerController.h"
#include "Raynet_FinalBuildGameModeBase.h"




void ARaynet_FinalBuildGameModeBase::createRoom_Implementation(bool offensive, APlayerController* PC) {
	if( HasAuthority() ) {
		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);

		auto room = GetWorld()->SpawnActor<ARoom>(Location, Rotation);
		room->SetReplicates(true);
		Cast<ARaynet_GameState>(GameState)->Rooms.AddUnique(room);
		room->RoomID = nextRoomId++;
		room->RoomStage = EGameStage::Waiting;
		room->Offensive = offensive;

		Cast<ARaynet_PlayerController>(PC)->roomin = room;
	}

}
void ARaynet_FinalBuildGameModeBase::joinRoom_Implementation(int32 RoomID, APlayerController* PC) {
	if( Cast<ARaynet_GameState>(GameState)->Rooms.IsValidIndex(RoomID) ) {
		auto room = Cast<ARaynet_GameState>(GameState)->Rooms[RoomID];
		if( room->RoomStage == EGameStage::Waiting ) {
			room->RoomStage = EGameStage::SetPawn_BothNF;
			Cast<ARaynet_PlayerController>(PC)->roomin = room;
		}
		else {
		}
	}
}

void ARaynet_FinalBuildGameModeBase::deleteRoom_Implementation(int32 RoomID) {
	Cast<ARaynet_GameState>(GameState)->Rooms.Remove(Cast<ARaynet_GameState>(GameState)->Rooms[RoomID]);
}

bool ARaynet_FinalBuildGameModeBase::deleteRoom_Validate(int32 RoomID) {
	return true;
}

bool ARaynet_FinalBuildGameModeBase::createRoom_Validate(bool offensive, APlayerController* PC) {
	return true;
}

bool ARaynet_FinalBuildGameModeBase::joinRoom_Validate(int32 RoomID, APlayerController* PC) {
	return true;
}

void ARaynet_FinalBuildGameModeBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARaynet_FinalBuildGameModeBase, nextRoomId);
}