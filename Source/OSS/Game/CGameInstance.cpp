#include "CGameInstance.h"

UCGameInstance::UCGameInstance()
{

}

void UCGameInstance::Init()
{
	Super::Init();
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