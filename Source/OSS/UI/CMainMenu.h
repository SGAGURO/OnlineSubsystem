#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/CMenuInterface.h"
#include "CMainMenu.generated.h"

class UButton;
class UWidgetSwitcher;
class UWidget;
class UEditableTextBox;

UCLASS()
class OSS_API UCMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

public:
	void SetOwningInstance(ICMenuInterface* InInstance);

	void Startup();
	void Shutdown();

private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void JoinServer();

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
	UButton* JoinButton;

	//Join Menu
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IPAddressField;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelJoinButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmJoinButton;

	
private:
	ICMenuInterface* OwningInstance;
};
