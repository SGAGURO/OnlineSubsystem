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

void UCMainMenu::Startup()
{
	AddToViewport(10);
	bIsFocusable = true;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC) return;

	PC->SetInputMode(InputMode);
	PC->bShowMouseCursor = true;
}

void UCMainMenu::Shutdown()
{
	RemoveFromViewport();
	bIsFocusable = false;

	FInputModeGameOnly InputMode;

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC) return;

	PC->SetInputMode(InputMode);
	PC->bShowMouseCursor = false;
}

void UCMainMenu::HostServer()
{
	OwningInstance->Host();
}