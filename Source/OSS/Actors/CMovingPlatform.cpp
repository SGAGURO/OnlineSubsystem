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
	
	WorldStartLocation = GetActorLocation();
	WorldTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void ACMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//This platfrom will only move on the server.
	if (HasAuthority())
	{
		FVector CurrentLocation = GetActorLocation();

		float TotalDistance = (WorldTargetLocation - WorldStartLocation).Size();
		float CurrentDistance = (CurrentLocation - WorldStartLocation).Size();
		
		if (CurrentDistance > TotalDistance)
		{
			FVector Temp = WorldStartLocation;
			WorldStartLocation = WorldTargetLocation;
			WorldTargetLocation = Temp;
		}

		FVector Direction = (WorldTargetLocation - CurrentLocation).GetSafeNormal();

		CurrentLocation += Direction * Speed * DeltaTime;

		SetActorLocation(CurrentLocation);
	}
}

