// Fill out your copyright notice in the Description page of Project Settings.

#include "Raynet_FinalBuild.h"
#include "Net/UnrealNetwork.h"
#include "Room.h"


// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bAlwaysRelevant = true;
	bReplicates = true;
	Board.Init(EPawn::Null, 64);
	Player1Terminal.Init(TERMINAL_CARD_UNUSED, 4);
	Player2Terminal.Init(TERMINAL_CARD_UNUSED, 4);
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom::addMove(FMove move) {
	switch( move.Type ) {
	case EMoveType::SetPawn:
		if( move.playerID == 1 ) {
			Board[vectorToInt(move.Point)] = move.additionalProperty?EPawn::Virus1:EPawn::Link1;
		}
		else {
			Board[vectorToInt(reverseVector(move.Point))] = move.additionalProperty ? EPawn::Virus2 : EPawn::Link2;
		}
		break;
	}
}

FVector2D ARoom::reverseVector(FVector2D in) {
	return FVector2D(7 - in.X, 7 - in.Y);
}

int32 ARoom::vectorToInt(FVector2D in) {
	return in.X + in.Y * 8;
}

void ARoom::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARoom, RoomID);
	DOREPLIFETIME(ARoom, Offensive);
	DOREPLIFETIME(ARoom, MoveStack);
	DOREPLIFETIME(ARoom, RoomStage);
	DOREPLIFETIME(ARoom, Board);
	DOREPLIFETIME(ARoom, Player1Terminal);
	DOREPLIFETIME(ARoom, Player2Terminal);
}
