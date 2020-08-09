#pragma once

#include "GameFramework/GameMode.h"
#include "BattleTankGameMode.generated.h"


/* // States of the game */
UENUM(BlueprintType, Meta = (Bitflags))
enum class EBT_PlayState : uint8
{
	/** Gets set when Player Controlled Tank enters the game (BeginPlay)*/
	EBT_Playing		 UMETA(DisplayName = "Playing"),
	EBT_GameOver	 UMETA(DisplayName = "GameOver"),
	EBT_MatchWon	 UMETA(DisplayName = "MatchWon"),
	EBT_InPause		 UMETA(DisplayName = "InPause"),
	EBT_InMainMenu	 UMETA(DisplayName = "InMainMenu"),
	EBT_Unknown		 UMETA(DisplayName = "Unknown")
};

UCLASS(BlueprintType, AutoExpandCategories = (Input, Tank, GameMode, BT))
class BATTLETANK_API ABattleTankGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABattleTankGameMode();

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|GameMode ")
	FORCEINLINE EBT_PlayState GetCurrentPlayState() const { return BT_PlayState; };

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|GameMode")
	void HandleNewPlayState(EBT_PlayState NewState);

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|GameMode")
	void SetCurrentPlayState(EBT_PlayState NewState);
protected:

private:
	/* // Keeps track of current state of the game */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ BT|GameMode ")
	EBT_PlayState BT_PlayState;
};
