// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionsSubsystem();

	void CreateSession(int32 NumPublicConnections, FString MatchType, bool bIsLAN, bool bIsPresence);

	void FindSessions(int32 MaxSearchResults, bool bIsLAN, bool bIsPresence);

	void JoinSession(const FOnlineSessionSearchResult& SessionResult);

	void DestroySession(const FOnlineSessionSearchResult& SessionResult);

	void StartSession(const FOnlineSessionSearchResult& SessionResult);

protected:
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnFindSessionComplete(int32 NumSearchResults, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& SearchResults);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	
private:
	IOnlineSessionPtr SessionInterface;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;

	FOnFindFriendSessionCompleteDelegate OnFindFriendSessionCompleteDelegate;

	FDelegateHandle OnFindFriendSessionCompleteDelegateHandle;

	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	
};
