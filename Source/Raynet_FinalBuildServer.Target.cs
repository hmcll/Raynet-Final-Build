// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class Raynet_FinalBuildServerTarget : TargetRules
{

    public Raynet_FinalBuildServerTarget(TargetInfo Target)

    {

        Type = TargetType.Server;

        bUsesSteam = true;

    }

    //
    // TargetRules interface.
    //
    public override void SetupBinaries
    (
     TargetInfo Target,
     ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
     ref List<string> OutExtraModuleNames
     )
    {
        OutExtraModuleNames.Add("Raynet_FinalBuild");
    }
}