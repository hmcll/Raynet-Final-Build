#pragma once

#include "EnumsAndStructs.generated.h"

UENUM(BlueprintType)
enum class EPawn:uint8 {
	Null = 0,
	Base1 = 1,
	Base2 = 2,
	Virus1 = 3,
	Virus2 = 4,
	Link1 = 5,
	Link2 = 6,
	LineBoostVirus1 = 7,
	LineBoostVirus2 = 8,
	LineBoostLink1 = 9,
	LineBoostLink2 = 10,
	FireWall1 = 11,
	FireWall2 = 12,
};

UENUM(BlueprintType)
enum class EGameStage:uint8 {
	Waiting,
	SetPawn_BothNF,
	SetPawn_OneF,
	Playing,
	Ending,
};

UENUM(BlueprintType)
enum class ETerminal:uint8 {
	LineBoost = 0, FireWall = 1, VirusCheck = 2, NotFound = 3
};

UENUM(BlueprintType)
enum class EMoveType:uint8 {
	SetPawn,
	Move,
	Lineboost,
	Firewall,
	Viruscheck,
	NotFound,
	GameEnd,
};

USTRUCT(BlueprintType)
struct FMove {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		EMoveType Type;
	UPROPERTY(BlueprintReadWrite)
		int32 playerID;
	UPROPERTY(BlueprintReadWrite)
		FVector2D Point = FVector2D(0.5,0.5);
	UPROPERTY(BlueprintReadWrite)
		FVector2D Point2 = FVector2D(0.5, 0.5);
	UPROPERTY(BlueprintReadWrite)
		bool additionalProperty;

};