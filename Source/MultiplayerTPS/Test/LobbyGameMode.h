#pragma once

#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayerController) override;
	virtual void Logout(AController* Exiting) override;
};
