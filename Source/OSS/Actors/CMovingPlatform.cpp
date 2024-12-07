#include "CMovingPlatform.h"

ACMovingPlatform::ACMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
	Speed = 20.f;
}

void ACMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += FVector(1, 0, 0) * Speed * DeltaTime;

	SetActorLocation(CurrentLocation);
}

