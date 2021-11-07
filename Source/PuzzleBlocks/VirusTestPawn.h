// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PuzzleBlocksBlock.h"
#include "VirusTestPawn.generated.h"

UCLASS()
class PUZZLEBLOCKS_API AVirusTestPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

public:
	// Sets default values for this pawn's properties
	AVirusTestPawn();

	UPROPERTY()
	class UMaterial* BaseMaterial;

	UPROPERTY()
	class APuzzleBlocksBlock* currentBlock;

	UPROPERTY()
	class APuzzleBlocksBlock* targetBlock;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector TargetLocation;
	FVector MovementVector;

	int32	dir;
	int32   infectCountdown;

	/** Choose a new target to move to */
	void setTarget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
