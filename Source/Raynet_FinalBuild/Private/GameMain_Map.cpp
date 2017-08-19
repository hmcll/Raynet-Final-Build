// Fill out your copyright notice in the Description page of Project Settings.

#include "Raynet_FinalBuild.h"
#include "GameMain_Map.h"



void AGameMain_Map::BeginPlay () {
#if PLATFORM_WINDOWS
	GSystemResolution.RequestResolutionChange ( 540, 960, EWindowMode::Windowed );
#endif
	AfterBeginPlay ();
}
