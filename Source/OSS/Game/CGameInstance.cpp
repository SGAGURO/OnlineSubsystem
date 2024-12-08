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
}

void UCGameInstance::Join(const FString& InAddress)
{
	UEngine* Engine = GetEngine();
	if (!Engine) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green,  FString::Printf(TEXT("Join to %s"), *InAddress));
}