#include "CGameInstance.h"
#include "UI/CMainMenu.h"

UCGameInstance::UCGameInstance()
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClass_Asset(TEXT("/Game/UI/WB_MainMenu"));
	if (MainMenuWidgetClass_Asset.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetClass_Asset.Class;
	}
}

void UCGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *GetNameSafe(MainMenuWidgetClass));
}

void UCGameInstance::LoadMainMenu()
{
	if (!ensure(MainMenuWidgetClass)) return;

	MainMenu = CreateWidget<UCMainMenu>(this, MainMenuWidgetClass);
	if (!MainMenu) return;

	MainMenu->SetOwningInstance(this);
	MainMenu->Startup();
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
	UEngine* Engine = GetEngine();
	if (!Engine) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green,  FString::Printf(TEXT("Join to %s"), *InAddress));

	APlayerController* PC = GetFirstLocalPlayerController();
	if (!PC) return;

	PC->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}