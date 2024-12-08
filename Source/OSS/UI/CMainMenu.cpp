#include "CMainMenu.h"
#include "Components/Button.h"

bool UCMainMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;
	if (!HostButton) return false;

	HostButton->OnClicked.AddDynamic(this, &UCMainMenu::HostServer);

	return true;
}

void UCMainMenu::SetOwningInstance(ICMenuInterface* InInstance)
{
	OwningInstance = InInstance;
}

void UCMainMenu::HostServer()
{
	OwningInstance->Host();
}