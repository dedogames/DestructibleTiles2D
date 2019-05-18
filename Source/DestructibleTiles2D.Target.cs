// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class DestructibleTiles2DTarget : TargetRules
{
	public DestructibleTiles2DTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "DestructibleTiles2D" } );
	}
}
