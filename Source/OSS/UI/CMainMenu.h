#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/CMenuInterface.h"
#include "CMainMenu.generated.h"

class UButton;

UCLASS()
class OSS_API UCMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

public:
	void SetOwningInstance(ICMenuInterface* InInstance);

	void Startup();
	void Shutdown();

private:
	UFUNCTION()
	void HostServer();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;
	
private:
	ICMenuInterface* OwningInstance;
};
