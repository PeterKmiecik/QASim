// Peter Kmiecik Art All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RPS_GameMode.generated.h"

/* // Playable shapes Rock,Paper,Scissors */
UENUM(BlueprintType)
enum class EPlayableShape : uint8
{
	EPS_Rock			UMETA(DisplayName = "Rock"),
	EPS_Paper			UMETA(DisplayName = "Paper"),
	EPS_Scissors		UMETA(DisplayName = "Scissors"),
	EPS_null			UMETA(DisplayName = "null")
};

/* // Playable shapes Rock,Paper,Scissors */
UENUM(BlueprintType)
enum class ERoundResult : uint8
{
	ERS_Player		UMETA(DisplayName = "Player"),
	ERS_CPU			UMETA(DisplayName = "CPU"),
	ERS_Null		UMETA(DisplayName = "null")
};

class ARPS_InGameHUD;
class URPS_MainGameWidget;

UCLASS(BlueprintType, AutoExpandCategories = (RPS, GameModeBase))
class ARPS_GameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ARPS_GameMode();

	UFUNCTION(BlueprintCallable, Category = "@@@ RPS|GameModeBase")
	FORCEINLINE ERoundResult GetRoundResult() const { return RoundResult; };

	UFUNCTION(BlueprintCallable, Category = "@@@ RPS|GameModeBase")
	FORCEINLINE EPlayableShape GetPlayableShape() const { return PlayableShape; };
	
	UFUNCTION(BlueprintCallable, Category = "@@@ RPS|GameModeBase")
	void PlayRound(EPlayableShape InShape);

	ARPS_InGameHUD* GetInGameHUD();

protected:
	virtual void BeginPlay() override;

private:
	void Init();
	EPlayableShape CPUShape;
	EPlayableShape PlayerShape;
	ARPS_InGameHUD* RPS_InGameHUD;
	FName PC;
	FName CPU;
	bool bPlayerGoesFirst;
	void SetRandCPUShape();
	URPS_MainGameWidget* GetMainGameWidget();

	/** Swaps Hand texture based on who needs swapping */
	void ChangeAttackTexture(EPlayableShape ActiveHandType, FName ForWho);

	/** Randomly see if player should start the round, CPU goes first otherwise*/
	bool DeterminePlayerRoundPriority();

	/** Return round time which has passed*/
	float TurnTimeElapsed();

	/** Checks which round is currently played 
	* based on number of TurnTimers expired to this moment from level start*/
	uint8 CalcRound();

	/** Based on actual Enum of shape for player or cpu, change thier hand image*/
	void DetermineAttackImage(EPlayableShape ActiveHandType, FName ForWho);

	/* // Who did wont this round*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|GameModeBase ")
	ERoundResult RoundResult;

	/* // Clicked playable RPS shape */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|GameModeBase ")
	EPlayableShape PlayableShape;

	/** Lenght of turn in seconds.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|GameModeBase ")
	uint8 TurnTimer;

	/** Maximum amount of rounds we can play until total score.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ RPS|GameModeBase ")
	uint8 MaxRounds;

	/** Current round number*/
	uint8 Round;

	/** Starts counting time from start of round in HUD*/
	void StartRoundTimer(float InTime);
};
