// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleBlocksGameMode.h"
#include "PuzzleBlocksPlayerController.h"
#include "PuzzleBlocksPawn.h"

APuzzleBlocksGameMode::APuzzleBlocksGameMode()
{
	// no pawn by default
	// DefaultPawnClass = APuzzleBlocksPawn::StaticClass();
	
	// use our own player controller class
	PlayerControllerClass = APuzzleBlocksPlayerController::StaticClass();
}
