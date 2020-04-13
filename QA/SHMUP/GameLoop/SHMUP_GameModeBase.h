// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SHMUP_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class QA_API ASHMUP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;


private:
	UFUNCTION()
	void OnShipDeath();

	UPROPERTY(EditDefaultsOnly, Category = "@@@@@ SHMUP GameModeBase")
		TSubclassOf<class ASHMUP_BasePawn> BasePawn;

};
