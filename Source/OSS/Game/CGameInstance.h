#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/CMenuInterface.h"
#include "CGameInstance.generated.h"

class UCMainMenu;

UCLASS()
class OSS_API UCGameInstance : public UGameInstance, public ICMenuInterface
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
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& InAddress) override;

private:
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UCMainMenu* MainMenu;
};
