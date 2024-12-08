#include "CMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "CServerRow.h"

UCMainMenu::UCMainMenu()
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowClass_Asset(TEXT("/Game/UI/WB_ServerRow"));
	if (ServerRowClass_Asset.Succeeded())
	{
		ServerRowClass = ServerRowClass_Asset.Class;
	}
}


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

	if (QuitButton == nullptr) return false;
	QuitButton->OnClicked.AddDynamic(this, &UCMainMenu::QuitGame);

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

	if (OwningInstance)
	{
		OwningInstance->RefreshServerList();
	}
}

void UCMainMenu::JoinServer()
{
	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index is %d."), SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index is not set."));
	}

	if (!OwningInstance) return;
	OwningInstance->Join("NotValid");
}

void UCMainMenu::QuitGame()
{
	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC) return;

	PC->ConsoleCommand("quit");
}

void UCMainMenu::SetServerList(TArray<FString> InServerNames)
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (!ServerList) return;
	ServerList->ClearChildren();

	uint32 i = 0;
	for (const FString& ServerName : InServerNames)
	{
		UCServerRow* ServerRow = CreateWidget<UCServerRow>(World, ServerRowClass);
		if (!ServerRow) return;

		ServerRow->ServerName->SetText(FText::FromString(ServerName));
		ServerRow->Setup(this, i++);

		ServerList->AddChild(ServerRow);
	}

}

void UCMainMenu::SetSelectedIndex(uint32 InIndex)
{
	SelectedIndex = InIndex;
}
