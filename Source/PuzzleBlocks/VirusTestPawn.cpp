#include "VirusTestPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

// Sets default values
AVirusTestPawn::AVirusTestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/SM_Rock.SM_Rock"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/M_Ground_Moss.M_Ground_Moss"))
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
	BlockMesh->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.5f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);

	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
}

void AVirusTestPawn::setTarget()
{
	targetBlock = nullptr;

	while (targetBlock == nullptr)
	{
		int32 d = FMath::RandRange(0, 5);

		targetBlock = currentBlock->adjacentBlock[d];
	}

	TargetLocation = targetBlock->GetActorLocation();
	TargetLocation.Z = GetActorLocation().Z;
	
	MovementVector = TargetLocation - GetActorLocation();
}

// Called when the game starts or when spawned
void AVirusTestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVirusTestPawn::Tick(float DeltaTime)
{
	FVector tempVector;
	;
	Super::Tick(DeltaTime);

	if (targetBlock == nullptr)
	{
		setTarget();
	}

	tempVector = GetActorLocation() + MovementVector / 50.f;
	
	if (abs(tempVector.X - TargetLocation.X) < 5 &&
		abs(tempVector.Y - TargetLocation.Y) < 5)
	{
		tempVector = TargetLocation;
	}
	
	SetActorLocation(tempVector,true);

	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;

	SetActorRotation(NewRotation);

	if (tempVector == TargetLocation)
	{
		currentBlock = targetBlock;
		targetBlock = nullptr;
	}
}

// Called to bind functionality to input
void AVirusTestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

