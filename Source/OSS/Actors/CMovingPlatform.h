#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CMovingPlatform.generated.h"

UCLASS()
class OSS_API ACMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	ACMovingPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

	//This is relative location from root component with 3D widget
	UPROPERTY(EditAnywhere, Category = "TargetPoint", meta = (MakeEditWidget))
	FVector TargetLocation;

private:
	FVector WorldStartLocation;
	FVector WorldTargetLocation;
};
