#include "QG_GameModeBase.h"

#include "QG_BPFL.h"
#include "QG_GlobalDefines.h"

#include "Quests\QuestManager.h"
#include "FirstPersonCharacter.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


AQG_GameModeBase::AQG_GameModeBase()
{
	// Default HUD state
	HUDState = EHUDState::HS_Ingame;
}

void AQG_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ApplyHUDChanges();
}

void AQG_GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQG_GameModeBase::ApplyHUDChanges()
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
	}

	switch (HUDState)
	{
	case EHUDState::HS_Ingame:
		ApplyHUD(InGamHUDClass,false,false, FInputModeGameOnly::FInputModeGameOnly());
		break;
	case EHUDState::HS_Inventory:
		ApplyHUD(InventoryHUDClass, true, true, FInputModeGameAndUI::FInputModeGameAndUI());
		break;
	case EHUDState::HS_Shop_General:
		ApplyHUD(ShopGeneralHUDClass, true, true, FInputModeUIOnly::FInputModeUIOnly());
		break;
	case EHUDState::HS_Shop_Weapon:
		ApplyHUD(InGamHUDClass, true, true, FInputModeGameOnly::FInputModeGameOnly());
		break;
	default:
		break;
	}
}

void AQG_GameModeBase::ChangeHUDState(EHUDState NewState)
{
	HUDState = NewState;
	ApplyHUDChanges();
}

bool AQG_GameModeBase::ApplyHUD(TSubclassOf<class UUserWidget> WidgetToApply, bool ShowMouseCursor, bool EnableClickEvents, const FInputModeDataBase& InInputMode /*= FInputModeGameAndUI()*/)
{
	AFirstPersonCharacter* MyCharacter = Cast<AFirstPersonCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	if (WidgetToApply != nullptr)
	{
		MyController->bShowMouseCursor = ShowMouseCursor;
		MyController->bEnableClickEvents = EnableClickEvents;
		MyController->SetInputMode(InInputMode);

		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),WidgetToApply);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
			return true;
		}
		else {
			UE_LOG(XXXXX_Log_QG, Error, TEXT("@@@@@ [%s] ApplyHUD(...) CurrentWidget == nullptr, it was not created properly"), *this->GetName());
			return false;
		}	
	}
	else {
		UE_LOG(XXXXX_Log_QG, Error, TEXT("@@@@@ [%s] ApplyHUD(...) WidgetToApply == nullptr, check GameMode UPROPERTY is set"), *this->GetName());
		return false;
	}
}