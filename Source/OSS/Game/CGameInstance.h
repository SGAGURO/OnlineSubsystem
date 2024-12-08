#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

UCLASS()
class OSS_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCGameInstance();

protected:
	virtual void Init() override;

public:
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& InAddress = "127.0.0.1");
	
};
