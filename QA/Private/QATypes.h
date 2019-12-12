// Peter Kmiecik Art All Rights Reserved

#pragma once


#include "CoreMinimal.h"
#include "QATypes.generated.h"

 /* // Enum containing Widgets of all games playable
* // leave Default empty
*
* // REMEMBER TO SET REFERENCES IN BP_QATypes ! 
*/
UENUM(BlueprintType)
enum class EGameModeWidgets : uint8
{
	Default			UMETA(DisplayName = "_DefaultEmpty_"),
	QA_MainGame		UMETA(DisplayName = "QA_MainGame"),
	SHMUP_Menu		UMETA(DisplayName = "SHMUP_Menu"),
	SHMUP_Game		UMETA(DisplayName = "SHMUP_Game"),
	FPS				UMETA(DisplayName = "FPS_Menu"),
};


class UQAUserWidget;

UCLASS(Blueprintable, BlueprintType)
class QA_API UQATypes : public UObject
{

	GENERATED_BODY()

public:
	UQATypes();
	~UQATypes();

	/* //  Enum containing Widgets of all games playable
	// leave Default empty   */
	UPROPERTY(BlueprintReadWrite, Category = "@@@ QA Enums")
	EGameModeWidgets eGameModeWidgets;

	/* // Map of EGameModes to UQAUserWidget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, BlueprintType, Category = "@@@ QA References")
	TMap < EGameModeWidgets, TSubclassOf<UQAUserWidget>> MGameModeWidgets;

};
