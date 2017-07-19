#pragma once

#include "EnumsAndStructs.generated.h"

UENUM(BlueprintType)
enum class EPawn:uint8 {
	Null,
	Base1,
	Base2,
	Virus1,
	Virus2,
	Link1,
	Link2,
	LineBoostVirus1,
	LineBoostVirus2,
	LineBoostLink1,
	LineBoostLink2,
	FireWall1,
	FireWall2,
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
	LineBoost, FireWall, VirusCheck, NotFound
};

UENUM(BlueprintType)
enum class EMoveType :uint8{
	SetPawn,
	Move,
	Lineboost,
	Firewall,
	Viruscheck,
	NotFound
};

USTRUCT(BlueprintType)
struct FMove {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		EMoveType Type;
	UPROPERTY(BlueprintReadWrite)
		int32 playerID;
	UPROPERTY(BlueprintReadWrite)
		FVector2D Point;
	UPROPERTY(BlueprintReadWrite)
		FVector2D Point2;
	UPROPERTY(BlueprintReadWrite)
		bool additionalProperty;

};