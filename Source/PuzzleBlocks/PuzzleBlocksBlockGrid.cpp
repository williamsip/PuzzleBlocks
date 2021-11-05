// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleBlocksBlockGrid.h"
#include "PuzzleBlocksBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

APuzzleBlocksBlockGrid::APuzzleBlocksBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 14;
	BlockSpacing = 300.f;
}

void APuzzleBlocksBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for(int32 x=0; x<Size; x++)
	{
		for (int32 y=0; y<Size; y++)
		{
			const float XOffset = (x - float(Size)/2) * BlockSpacing;
			const float YOffset = (float(y) - float(Size)/2 + float(x%2)/2) * (BlockSpacing + 30);

			// Make position vector, offset from Grid location
			const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

			// Spawn a block
			APuzzleBlocksBlock* NewBlock = GetWorld()->SpawnActor<APuzzleBlocksBlock>(BlockLocation, FRotator(0,0,0));

			// Tell the block about its owner
			if (NewBlock != nullptr)
			{
				NewBlock->OwningGrid = this;

				blockArray.Add(NewBlock);
			}
		}
	}

	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			int32 z;
			
			if (x%2)
			{
				z = 1;
			}
			else
			{
				z = -1;
			}

			APuzzleBlocksBlock* ThisBlock = getBlockAtCoord(x, y);
			ThisBlock->adjacentBlock[0] = getBlockAtCoord(x+1, y);
			ThisBlock->adjacentBlock[1] = getBlockAtCoord(x, y+1);
			ThisBlock->adjacentBlock[2] = getBlockAtCoord(x-1, y);
			ThisBlock->adjacentBlock[3] = getBlockAtCoord(x, y-1);
			ThisBlock->adjacentBlock[4] = getBlockAtCoord(x+1, y+z);
			ThisBlock->adjacentBlock[5] = getBlockAtCoord(x-1, y+z);
		}
	}
}

APuzzleBlocksBlock* APuzzleBlocksBlockGrid::getBlockAtCoord(int32 x, int32 y)
{
	if (x>=0 && y>=0 && x<Size && y<Size)
	{
		return blockArray[x*Size + y];
	}

	return nullptr;
}

void APuzzleBlocksBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
