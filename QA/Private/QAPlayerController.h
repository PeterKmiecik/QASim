// Peter Kmiecik Art All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QATypes.h"
#include "QAPlayerController.generated.h"

/**
 * 
 */

class UQAUserWidget;


UCLASS()
class AQAPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	AQAPlayerController();




protected:
	virtual void BeginPlay() override;

};
