#pragma once

#include "CoreMinimal.h"
#include "CMenuBase.h"
#include "CMainMenu.generated.h"

class UButton;
class UWidgetSwitcher;
class UWidget;
class UPanelWidget;

UCLASS()
class OSS_API UCMainMenu : public UCMenuBase
{
	GENERATED_BODY()

public:
	UCMainMenu();

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void QuitGame();

public:
	void SetServerList(TArray<FString> InServerNames);
	void SetSelectedIndex(uint32 InIndex);

private:
	//Menu Switcher
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	//Main Menu
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	//Join Menu
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ServerList;

	TSubclassOf<UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelJoinButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmJoinButton;

private:
	TOptional<uint32> SelectedIndex;
};
