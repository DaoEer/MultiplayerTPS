// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Components/Button.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch)
{
	PublicConnectionsNumber = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);

	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionCompleteDelegate.AddUObject(this, &UMenu::OnCreateSessionComplete);
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionCompleteDelegate.AddUObject(this, &UMenu::OnFindSessionComplete);
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionCompleteDelegate.AddUObject(this, &UMenu::OnJoinSessionComplete);
		MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionCompleteDelegate.AddUObject(this, &UMenu::OnDestroySessionComplete);
		MultiplayerSessionsSubsystem->MultiplayerOnStartSessionCompleteDelegate.AddUObject(this, &UMenu::OnStartSessionComplete);
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UMenu::OnHostButtonClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMenu::OnJoinButtonClicked);
	}

	return true;
}

void UMenu::OnHostButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(PublicConnectionsNumber, MatchType);
	}
}

void UMenu::OnJoinButtonClicked()
{
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->FindSessions(100);
	}
}

void UMenu::OnCreateSessionComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Yellow,
		FString::Printf(TEXT("CreateSession: %s"), bWasSuccessful ? TEXT("Success") : TEXT("Failure"))
	);

	if (!bWasSuccessful)
	{
		return;
	}

	if (!LobbyLevelPath.IsEmpty())
	{
		if (UWorld* World = GetWorld())
		{
			World->ServerTravel(LobbyLevelPath);
		}
	}
}

void UMenu::OnFindSessionComplete(bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& SearchResults)
{
	if (!MultiplayerSessionsSubsystem)
	{
		return;
	}
	
	for (const FOnlineSessionSearchResult& Result : SearchResults)
	{
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);
		if (SettingsValue == MatchType)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Green,
				FString::Printf(TEXT("Found session: %s"), *Result.GetSessionIdStr())
			);
			MultiplayerSessionsSubsystem->JoinSession(Result);
			return;
		}
	}
}

void UMenu::OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result)
{
	if (IOnlineSubsystem* Subsystem = Online::GetSubsystem(UObject::GetWorld()))
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

			if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
			{
				PlayerController->ClientTravel(Address, TRAVEL_Absolute);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					15.f,
					FColor::Red,
					TEXT("Failed to get PlayerController for travel.")
				);
			}
		}
	}
}

void UMenu::OnDestroySessionComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Yellow,
		FString::Printf(TEXT("DestroySession: %s"), bWasSuccessful ? TEXT("Success") : TEXT("Failure"))
	);
}

void UMenu::OnStartSessionComplete(bool bWasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Yellow,
		FString::Printf(TEXT("StartSession: %s"), bWasSuccessful ? TEXT("Success") : TEXT("Failure"))
	);
}
