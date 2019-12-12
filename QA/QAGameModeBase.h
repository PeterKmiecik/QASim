// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QAGameModeBase.generated.h"


/* // all playable games GameModes */
//UENUM(BlueprintType)
//enum class EGameModes : uint8
//{
//	Default  UMETA(DisplayName = "_DefaultEmpty_")
//
//};

// COPY it to public and uncomment for easy access in BPs. //enum member variable instance
//  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enum")
//	ENameOfEnum InstanceObjectName;


/**
 * 
 */
UCLASS()
class QA_API AQAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, BlueprintType, Category = "@@@ QA Enums")
	EGameModes EGameModes;*/

};
