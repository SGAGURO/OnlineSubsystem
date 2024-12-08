#include "CMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UCMainMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;
	
	if (!HostButton) return false;
	HostButton->OnClicked.AddDynamic(this, &UCMainMenu::HostServer);

	if (!JoinButton) return false;
	JoinButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenJoinMenu);

	if (!CancelJoinButton) return false;
	CancelJoinButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenMainMenu);

	if (ConfirmJoinButton == nullptr) return false;
	ConfirmJoinButton->OnClicked.AddDynamic(this, &UCMainMenu::JoinServer);

	return true;
}

void UCMainMenu::HostServer()
{
	OwningInstance->Host();
}

void UCMainMenu::OpenMainMenu()
{
	if (!MenuSwitcher) return;
	if (!MainMenu) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UCMainMenu::OpenJoinMenu()
{
	if (!MenuSwitcher) return;
	if (!JoinMenu) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UCMainMenu::JoinServer()
{
	if (!OwningInstance) return;
	
	if (!IPAddressField) return;

	const FString& Address = IPAddressField->GetText().IsEmpty() ? 
		"127.0.0.1" : 
		IPAddressField->GetText().ToString();

	OwningInstance->Join(Address);
}
