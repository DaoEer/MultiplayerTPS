// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"

UCLASS()
class MULTIPLAYERTPS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LobbyLevelPath = FString(TEXT("/Game/Maps/Lobby"));

protected:
	virtual bool Initialize() override;
	
	UFUNCTION()
	void OnHostButtonClicked();
	UFUNCTION()
	void OnJoinButtonClicked();

	UFUNCTION()
	void OnCreateSessionComplete(bool bWasSuccessful);
	void OnFindSessionComplete(bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& SearchResults);
	void OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySessionComplete(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSessionComplete(bool bWasSuccessful);

private:
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta=(BindWidget))
	UButton* JoinButton;

	int32 PublicConnectionsNumber;
	FString MatchType;
};
