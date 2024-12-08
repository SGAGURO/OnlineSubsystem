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

void UCMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Host Button Clicked"));
}