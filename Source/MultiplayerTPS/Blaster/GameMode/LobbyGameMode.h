#pragma once
#include "BlasterGameModeBase.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class ALobbyGameMode : public ABlasterGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
