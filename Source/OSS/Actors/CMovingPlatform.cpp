#include "CMovingPlatform.h"

ACMovingPlatform::ACMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
	Speed = 20.f;

	//Enable Actor replicates & movement
	bReplicates = true;
	SetReplicateMovement(true);
}

void ACMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//This platfrom will only move on the server.
	if (HasAuthority())
	{
		FVector CurrentLocation = GetActorLocation();
		
		FVector WorldTargetLocation = GetTransform().TransformPosition(TargetLocation);
		FVector Direction = (WorldTargetLocation - CurrentLocation).GetSafeNormal();

		CurrentLocation += Direction * Speed * DeltaTime;

		SetActorLocation(CurrentLocation);
	}
}

