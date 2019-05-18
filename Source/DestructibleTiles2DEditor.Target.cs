// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class DestructibleTiles2DEditorTarget : TargetRules
{
	public DestructibleTiles2DEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "DestructibleTiles2D" } );
	}
}
