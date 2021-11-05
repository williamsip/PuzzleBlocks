// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleBlocksPlayerController.h"

APuzzleBlocksPlayerController::APuzzleBlocksPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
