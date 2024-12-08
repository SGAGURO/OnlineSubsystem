#include "CGameInstance.h"
#include "OnlineSubsystem.h"
#include "UI/CMainMenu.h"
#include "UI/CMenuBase.h"

UCGameInstance::UCGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClass_Asset(TEXT("/Game/UI/WB_MainMenu"));
	if (MainMenuWidgetClass_Asset.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetClass_Asset.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuWidgetClass_Asset(TEXT("/Game/UI/WB_PauseMenu"));
	if (PauseMenuWidgetClass_Asset.Succeeded())
	{
		PauseMenuWidgetClass = PauseMenuWidgetClass_Asset.Class;
	}
}

void UCGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		UE_LOG(LogTemp, Warning, TEXT("OSS : %s is avaliable."), *OSS->GetSubsystemName().ToString());

		IOnlineSessionPtr SessionInterface = OSS->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("SessionInterface is founded."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not found subsystem."));
	}
}

void UCGameInstance::LoadMainMenu()
{
	if (!ensure(MainMenuWidgetClass)) return;

	MainMenu = CreateWidget<UCMainMenu>(this, MainMenuWidgetClass);
	if (!MainMenu) return;

	MainMenu->SetOwningInstance(this);
	MainMenu->Startup();
}

void UCGameInstance::LoadPauseMenu()
{
	if (!ensure(PauseMenuWidgetClass)) return;

	UCMenuBase* PauseMenu = CreateWidget<UCMenuBase>(this, PauseMenuWidgetClass);
	if (!PauseMenu) return;

	PauseMenu->SetOwningInstance(this);
	PauseMenu->Startup();
}

void UCGameInstance::Host()
{
	if (MainMenu)
	{
		MainMenu->Shutdown();
	}

	UEngine* Engine = GetEngine();
	if (!Engine) return;
	
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Host"));

	UWorld* World = GetWorld();
	if (!World) return;

	World->ServerTravel("/Game/Maps/Coop?listen");
}

void UCGameInstance::Join(const FString& InAddress)
{
	if (MainMenu)
	{
		MainMenu->Shutdown();
	}

	UEngine* Engine = GetEngine();
	if (!Engine) return;

	Engine->AddOnScreenDebugMessage(0, 10, FColor::Green,  FString::Printf(TEXT("Join to %s"), *InAddress));

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC) return;

	PC->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::OpenMainMenuLevel()
{
	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC) return;

	PC->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}
