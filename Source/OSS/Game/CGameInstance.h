#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

class UUserWidget;

UCLASS()
class OSS_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCGameInstance();

protected:
	virtual void Init() override;

public:
	UFUNCTION(BlueprintCallable, Exec)
	void LoadMainMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& InAddress = "127.0.0.1");

private:
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};
