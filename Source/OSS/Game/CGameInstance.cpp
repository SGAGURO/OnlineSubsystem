#include "CGameInstance.h"
#include "Blueprint/UserWidget.h"

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

	UUserWidget* MainMenu = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
	if (!MainMenu) return;

	MainMenu->AddToViewport(10);
	MainMenu->bIsFocusable = true;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(MainMenu->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	APlayerController* PC = GetFirstLocalPlayerController();
	PC->SetInputMode(InputMode);
	PC->bShowMouseCursor = true;
}

void UCGameInstance::Host()
{
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