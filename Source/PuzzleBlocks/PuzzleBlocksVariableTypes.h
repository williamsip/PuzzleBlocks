// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BluePrintType)
enum class EPuzzleBlocksBlockColour : uint8
{
	Pink UMETA(DisplayName = "Pink"),
	Green UMETA(DisplayName = "Green"),
	Black UMETA(DisplayName = "Black"),
	Hole UMETA(DisplayName = "Hole")
};
