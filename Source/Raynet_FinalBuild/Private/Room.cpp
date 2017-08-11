// Fill out your copyright notice in the Description page of Project Settings.

#include "Raynet_FinalBuild.h"
#include "Net/UnrealNetwork.h"
#include "Room.h"


// Sets default values
ARoom::ARoom() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bAlwaysRelevant = true;
	bReplicates = true;
	Board.Init(EPawn::Null, 64);
	Player1Terminal.Init(TERMINAL_CARD_UNUSED, 4);
	Player2Terminal.Init(TERMINAL_CARD_UNUSED, 4);
}

// Called when the game starts or when spawned
void ARoom::BeginPlay() {
	Super::BeginPlay();
	VC1 = -1;
	VC2 = -1;
}

// Called every frame
void ARoom::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ARoom::addMove(FMove move) {
	if( move.playerID == 2 ) {
		move.Point = reverseVector(move.Point);
		move.Point2 = reverseVector(move.Point2);
	}
	switch( move.Type ) {
	case EMoveType::SetPawn:
		if( move.playerID == 1 ) {
			Board[vectorToInt(move.Point)] = move.additionalProperty ? EPawn::Virus1 : EPawn::Link1;
		}
		else {
			Board[vectorToInt(move.Point)] = move.additionalProperty ? EPawn::Virus2 : EPawn::Link2;
		}
		break;
	case EMoveType::Move:
		if( move.playerID == 1 ) {
			if( move.additionalProperty ) {
				if( vectorToInt(move.Point) == VC2 ) {
					VC2 = -1;
					ServerShowingOff2 = Board[vectorToInt(move.Point)];
				}
				if( Board[vectorToInt(move.Point)] == EPawn::Virus1 ) {
					P2SEV++;
					Board[vectorToInt(move.Point)] = EPawn::Null;
				}
				else if( Board[vectorToInt(move.Point)] == EPawn::Link1 ) {
					P2SEL++;
					Board[vectorToInt(move.Point)] = EPawn::Null;
					if( P1DBL + P2SEL == 4 ) {

						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Win
					}
				}
				else if( Board[vectorToInt(move.Point)] == EPawn::LineBoostVirus1 ) {
					P2SEV++;
					Player1Terminal[0] = TERMINAL_CARD_UNUSED;
					Board[vectorToInt(move.Point)] = EPawn::Null;
				}
				else if( Board[vectorToInt(move.Point)] == EPawn::LineBoostLink1 ) {
					P2SEL++;
					Player1Terminal[0] = TERMINAL_CARD_UNUSED;
					Board[vectorToInt(move.Point)] = EPawn::Null;
					if( P1DBL + P2SEL == 4 ) {

						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Win
					}
				}
			}
			else {
				if( vectorToInt(move.Point) == VC2 ) {
					VC2 = vectorToInt(move.Point2);
				}
				if( vectorToInt(move.Point2) == VC1 ) {
					VC1 = -1;
				}
				if( Board[vectorToInt(move.Point2)] == EPawn::Virus2 ) {
					P1DBV++;
					if( P1DBV == 4 ) {

						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.additionalProperty = true;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Lost
					}
					Board[vectorToInt(move.Point2)] = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = EPawn::Null;
				}
				else if( Board[vectorToInt(move.Point2)] == EPawn::Link2 ) {
					P1DBL++;

					if( P1DBL + P2SEL == 4 ) {
						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Win
					}
					Board[vectorToInt(move.Point2)] = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = EPawn::Null;

				}
				else if( Board[vectorToInt(move.Point2)] == EPawn::LineBoostVirus2 ) {
					P1DBV++;
					Player2Terminal[0] = TERMINAL_CARD_UNUSED;
					if( P1DBV == 4 ) {
						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.additionalProperty = true;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Lost
					}
					Board[vectorToInt(move.Point2)] = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = EPawn::Null;
				}
				else if( Board[vectorToInt(move.Point2)] == EPawn::LineBoostLink2 ) {
					P1DBL++;
					Player2Terminal[0] = TERMINAL_CARD_UNUSED;
					if( P1DBL + P2SEL == 4 ) {
						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Win
					}
					Board[vectorToInt(move.Point2)] = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = EPawn::Null;

				}
				else {
					auto temp = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = Board[vectorToInt(move.Point2)];
					Board[vectorToInt(move.Point2)] = temp;
				}
			}
		}
		else {
			if( move.additionalProperty ) {
				if( vectorToInt(move.Point) == VC1 ) {
					VC1 = -1;
					ServerShowingOff1 = Board[vectorToInt(move.Point)];
				}
				if( Board[vectorToInt(move.Point)] == EPawn::Virus2 ) {
					P1SEV++;
					Board[vectorToInt(move.Point)] = EPawn::Null;
				}
				else if( Board[vectorToInt(move.Point)] == EPawn::Link2 ) {
					P1SEL++;
					Board[vectorToInt(move.Point)] = EPawn::Null;
					if( P2DBL + P1SEL == 4 ) {

						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Win
					}
				}
				else if( Board[vectorToInt(move.Point)] == EPawn::LineBoostVirus2 ) {
					P1SEV++;
					Player2Terminal[0] = TERMINAL_CARD_UNUSED;
					Board[vectorToInt(move.Point)] = EPawn::Null;
				}
				else if( Board[vectorToInt(move.Point)] == EPawn::LineBoostLink2 ) {
					P1SEL++;
					Player2Terminal[0] = TERMINAL_CARD_UNUSED;
					Board[vectorToInt(move.Point)] = EPawn::Null;
					if( P2DBL + P1SEL == 4 ) {
						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Win
					}
				}
			}
			else {
				

				if( vectorToInt(move.Point) == VC1 ) {
					VC1 = vectorToInt(move.Point2);
				}
				if( vectorToInt(move.Point2) == VC2 ) {
					VC2 = -1;
				}

				if( Board[vectorToInt(move.Point2)] == EPawn::Virus1 ) {
					P2DBV++;
					if( P2DBV == 4 ) {
						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.additionalProperty = true;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Lost
					}
					Board[vectorToInt(move.Point2)] = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = EPawn::Null;
				}
				else if( Board[vectorToInt(move.Point2)] == EPawn::Link1 ) {
					P2DBL++;

					if( P2DBL + P1SEL == 4 ) {
						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Win
					}
					Board[vectorToInt(move.Point2)] = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = EPawn::Null;

				}
				else if( Board[vectorToInt(move.Point2)] == EPawn::LineBoostVirus1 ) {
					P2DBV++;
					Player1Terminal[0] = TERMINAL_CARD_UNUSED;
					if( P2DBV == 4 ) {
						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.additionalProperty = true;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Lost
					}
					Board[vectorToInt(move.Point2)] = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = EPawn::Null;
				}
				else if( Board[vectorToInt(move.Point2)] == EPawn::LineBoostLink1 ) {
					P2DBL++;
					Player1Terminal[0] = TERMINAL_CARD_UNUSED;
					if( P2DBL + P1SEL == 4 ) {
						MoveStack.Add(move);
						FMove nextMove;
						nextMove.Type = EMoveType::GameEnd;
						nextMove.playerID = move.playerID;
						MoveStack.Add(nextMove);
						return;
						// Add Move Win
					}
					Board[vectorToInt(move.Point2)] = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = EPawn::Null;

				}
				else {
					auto temp = Board[vectorToInt(move.Point)];
					Board[vectorToInt(move.Point)] = Board[vectorToInt(move.Point2)];
					Board[vectorToInt(move.Point2)] = temp;
				}
			}
		}
		break;
	case EMoveType::Lineboost:
		if( move.playerID == 1 ) {
			Player1Terminal[0] = !Player1Terminal[0];
		}
		else {
			Player2Terminal[0] = !Player2Terminal[0];
		}
		Board[vectorToInt(move.Point)] = ToggleLineBoost(Board[vectorToInt(move.Point)]);
		break;
	case EMoveType::Firewall:
		if( move.playerID == 1 ) {
			Player1Terminal[1] = !Player1Terminal[1];
		}
		else {
			Player2Terminal[1] = !Player2Terminal[1];
		}
		switch( Board[vectorToInt(move.Point)] ) {
		case EPawn::FireWall1:
		case EPawn::FireWall2:
			Board[vectorToInt(move.Point)] = EPawn::Null;
			break;
		case EPawn::Null:
			if( move.playerID == 1 ) {
				Board[vectorToInt(move.Point)] = EPawn::FireWall1;
			}
			else {
				Board[vectorToInt(move.Point)] = EPawn::FireWall2;
			}
			break;
		}
		break;
	case EMoveType::Viruscheck:
		if( move.playerID == 1 ) {
			Player1Terminal[2] = TERMINAL_CARD_USED;
			VC1 = vectorToInt(move.Point);
		}
		else {
			Player2Terminal[2] = TERMINAL_CARD_USED;
			VC2 = vectorToInt(move.Point);
		}
		break;
	case EMoveType::NotFound:
		if( move.additionalProperty ) {
			auto temp = Board[vectorToInt(move.Point)];
			Board[vectorToInt(move.Point)] = Board[vectorToInt(move.Point2)];
			Board[vectorToInt(move.Point2)] = temp;
			if( (uint8(Board[vectorToInt(move.Point)]) <=10&& uint8(Board[vectorToInt(move.Point)]) >= 7 )|| (uint8(Board[vectorToInt(move.Point2)]) <= 10 && uint8(Board[vectorToInt(move.Point2)]) >= 7 )) {
				Board[vectorToInt(move.Point)] = ToggleLineBoost(Board[vectorToInt(move.Point)]);
				Board[vectorToInt(move.Point2)] = ToggleLineBoost(Board[vectorToInt(move.Point2)]);
			}
		}
		if( vectorToInt(move.Point) == VC1 ) {
			VC1 = -1;
		}
		if( vectorToInt(move.Point2) == VC1 ) {
			VC1 = -1;
		}
		if( vectorToInt(move.Point) == VC2 ) {
			VC2 = -1;
		}
		if( vectorToInt(move.Point2) == VC2 ) {
			VC2 = -1;
		}
		if( move.playerID == 1 ) {
			Player1Terminal[3] = TERMINAL_CARD_USED;
		}
		else {
			Player2Terminal[3] = TERMINAL_CARD_USED;
		}

		break;
	}

	MoveStack.Add(move);
}

FVector2D ARoom::reverseVector(FVector2D in) {
	return FVector2D(7 - in.X, 7 - in.Y);
}

int32 ARoom::vectorToInt(FVector2D in) {
	return in.X + in.Y * 8;
}

EPawn ARoom::ToggleLineBoost(EPawn from) {
	switch( from ) {
	case EPawn::Virus1:
		return EPawn::LineBoostVirus1;
		break;
	case EPawn::Virus2:
		return EPawn::LineBoostVirus2;
		break;
	case EPawn::Link1:
		return EPawn::LineBoostLink1;
		break;
	case EPawn::Link2:
		return EPawn::LineBoostLink2;
		break;
	case EPawn::LineBoostVirus1:
		return EPawn::Virus1;
		break;
	case EPawn::LineBoostVirus2:
		return EPawn::Virus2;
		break;
	case EPawn::LineBoostLink1:
		return EPawn::Link1;
		break;
	case EPawn::LineBoostLink2:
		return EPawn::Link2;
		break;
	}
	return EPawn::Null;

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

	DOREPLIFETIME(ARoom, VC1);
	DOREPLIFETIME(ARoom, VC2);

	DOREPLIFETIME(ARoom, ServerShowingOff1);
	DOREPLIFETIME(ARoom, ServerShowingOff2);

	DOREPLIFETIME(ARoom, P1DBV);
	DOREPLIFETIME(ARoom, P1DBL);
	DOREPLIFETIME(ARoom, P1SEV);
	DOREPLIFETIME(ARoom, P1SEL);
	DOREPLIFETIME(ARoom, P2DBV);
	DOREPLIFETIME(ARoom, P2DBL);
	DOREPLIFETIME(ARoom, P2SEV);
	DOREPLIFETIME(ARoom, P2SEL);

}
