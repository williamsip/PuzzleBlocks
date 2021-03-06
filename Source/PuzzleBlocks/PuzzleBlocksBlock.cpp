// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleBlocksBlock.h"
#include "PuzzleBlocksBlockGrid.h"
#include "VirusTestPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

APuzzleBlocksBlock::APuzzleBlocksBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> GreenMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> PinkMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BlackMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/hextile_mesh.hextile_mesh")) // PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, GreenMaterial(TEXT("/Game/Puzzle/Meshes/M_Ground_Moss.M_Ground_Moss"))
			, PinkMaterial(TEXT("/Game/Puzzle/Meshes/M_Brick_Clay_New.M_Brick_Clay_New")) // BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, BlackMaterial(TEXT("/Game/Puzzle/Meshes/M_Tech_Hex_Tile.M_Tech_Hex_Tile")) // OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(3.f,3.f,3.f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.PinkMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &APuzzleBlocksBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &APuzzleBlocksBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	PinkMaterial = ConstructorStatics.PinkMaterial.Get();
	GreenMaterial = ConstructorStatics.GreenMaterial.Get();
	BlackMaterial = ConstructorStatics.BlackMaterial.Get();

	colour = EPuzzleBlocksBlockColour::Pink;
}

void APuzzleBlocksBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}

void APuzzleBlocksBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void APuzzleBlocksBlock::HandleClicked()
{
	// Check we are not already active
	/*
	if (!bIsActive)
	{
		bIsActive = true;

		// Change material
		BlockMesh->SetMaterial(0, OrangeMaterial);

		for (int32 i = 0; i < 6; i++)
		{
			if (adjacentBlock[i] != nullptr)
			{
				adjacentBlock[i]->BlockMesh->SetMaterial(0,BaseMaterial);
			}
		}

		// Tell the Grid
		if (OwningGrid != nullptr)
		{
			OwningGrid->AddScore();
		}
		*/

		// Make position vector, offset from Grid location
		const FVector BlockLocation = GetActorLocation() + FVector(0.f,0.f,40.F);

		// Spawn a virus
		AVirusTestPawn* NewVirus = GetWorld()->SpawnActor<AVirusTestPawn>(BlockLocation, FRotator(0, 0, 0));
		NewVirus->currentBlock = this;
	// }
}

void APuzzleBlocksBlock::Highlight(bool bOn)
{
}

void APuzzleBlocksBlock::setColour(EPuzzleBlocksBlockColour newColour)
{
	colour = newColour;
	
	switch (colour)
	{
		case EPuzzleBlocksBlockColour::Pink :
			BlockMesh->SetMaterial(0, PinkMaterial);
			break;

		case EPuzzleBlocksBlockColour::Green:
			BlockMesh->SetMaterial(0, GreenMaterial);
			break;

		case EPuzzleBlocksBlockColour::Black:
			BlockMesh->SetMaterial(0, BlackMaterial);
			break;
	}

}
