#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
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

	UFUNCTION(BlueprintCallable)
	void LoadPauseMenu();

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& InAddress) override;

	void OpenMainMenuLevel() override;

private:
	void OnCreateSessionComplete(FName InSessionName, bool InSuccess);
	void OnDestroySessionComplete(FName InSessionName, bool InSuccess);

	void CreateSession();

private:
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UCMainMenu* MainMenu;

	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	IOnlineSessionPtr SessionInterface;
};
