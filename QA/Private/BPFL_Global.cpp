
#include "BPFL_Global.h"
#include "QA.h"
#include "QA/Private/UI/QAUserWidget.h"
#include "QAGameModeBase.h"
#include "Core/QA_GameInstance.h"

#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Engine/StreamableManager.h"

DEFINE_LOG_CATEGORY(XXXX_Log_QA);
DEFINE_LOG_CATEGORY(XXXXX_Log_SHMUP);

AQAGameModeBase* GetQAGameModeFromContextObject(class UObject* WorldContextObject)
{
	UWorld* const MyWorld = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	check(MyWorld);

	AQAGameModeBase* const MyGame = MyWorld->GetAuthGameMode<AQAGameModeBase>();
	return MyGame;
}

float UBPFL_Global::DotToTarget(AActor* FromActor, AActor* TargetActor, FString FromWhereErrorMsg)
{
	if (!FromActor) {
		UE_LOG(XXXX_Log_QA, Warning, TEXT("@@@ [QA] [BPFL_Global] function called from [%s]: DotToTarget() parameter: FromActor passed was nullptr"), *FromWhereErrorMsg);
		return -2.f;}
	if (!TargetActor) {
		UE_LOG(XXXX_Log_QA, Warning, TEXT("@@@ [QA] [BPFL_Global] function called from [%s]: DotToTarget() parameter: TargetActor passed was nullptr"), *FromWhereErrorMsg);
		return -2.f;}
	FVector FromActorLocation = FromActor->GetActorLocation();
	FVector DirectionToTarget = (TargetActor->GetActorLocation() - FromActorLocation).GetSafeNormal2D();
	return FVector::DotProduct(FromActor->GetActorForwardVector(), DirectionToTarget);
}

FName UBPFL_Global::OpenLevel (UObject* WorldContextObject, TSoftObjectPtr<UObject> NextLevel, float Delay, float TimerRate, FString FromWhereErrorMsg)
{
	if (!WorldContextObject) return FName();

	FStreamableManager Streamable;
	if (NextLevel.IsPending())
	{
		const FSoftObjectPath& AssetRef = NextLevel.ToSoftObjectPath();
		NextLevel = Cast<UObject>(Streamable.LoadSynchronous(AssetRef));
	}

	if (!NextLevel.Get()) { 
		UE_LOG(XXXX_Log_QA, Error, TEXT("@@@ [QA] [BPFL_Global] function called from [%s] OpenLevel() NextLevel is not valid."), *FromWhereErrorMsg);
		return FName(); }

	UWorld* const MyWorld = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	check(MyWorld);
	FTimerManager& TimerManager = MyWorld->GetTimerManager();

	FString Empty = "Empty";
	FString* Left = &Empty;
	FString* Right = &Empty;
	bool bLevelNameSplit = NextLevel.ToString().Split(".", Left, Right);

	FName LevelToLoadName = UKismetStringLibrary::Conv_StringToName(*Left);
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TimerManager.ClearTimer(TimerHandle);

	if (GetBPFL_GlobalObject(WorldContextObject))
	{
		TimerDel.BindUFunction(GetBPFL_GlobalObject(WorldContextObject), FName("OpenLevelDelayed"), bLevelNameSplit, WorldContextObject, LevelToLoadName);
		TimerManager.SetTimer(TimerHandle, TimerDel, TimerRate, false, Delay);
	}
	else
	{
		UE_LOG(XXXX_Log_QA, Error, TEXT("@@@ [QA] [BPFL_Global] UBPFL_GlobalObject not vaild"));
	}
	return	bLevelNameSplit ? LevelToLoadName : FName();
}

void UBPFL_Global::OpenLevelDelayed(bool LevelNameWasSplit, UObject* WorldContextObject, FName LevelToLoadName)
{
	UE_LOG(XXXX_Log_QA, Log, TEXT("@@@ [QA] [BPFL_Global] OpenedLevel: %s"), *LevelToLoadName.ToString());
	LevelNameWasSplit ? UGameplayStatics::OpenLevel(WorldContextObject, LevelToLoadName) : false;
}

UBPFL_Global* UBPFL_Global::GetBPFL_GlobalObject(UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		UE_LOG(XXXX_Log_QA, Error, TEXT("@@@ [QA] [BPFL_Global] function: GetUBPFL_GlobalObject(...) WorldContextObject not vaild"));
		return nullptr;
	}
	return GetQA_GameInstance(WorldContextObject) ? GetQA_GameInstance(WorldContextObject)->GetBPFL_GlobalObject() : nullptr;
}


void UBPFL_Global::CacheBPFL_GlobalObjectRef(UQA_GameInstance* InGameInstance, UObject* WorldContextObject)
{
	if (!InGameInstance) {
		UE_LOG(XXXX_Log_QA, Error, TEXT("@@@ [QA] [BPFL_Global] function: CacheGameInstanceRef(...) parameter InGameInstance not vaild"));
		return;
	}
	InGameInstance->SetBPFL_GlobalObject(UBPFL_Global::StaticClass()->GetDefaultObject<UBPFL_Global>(), WorldContextObject);
}

UQA_GameInstance* UBPFL_Global::GetQA_GameInstance(UObject* WorldContextObject)
{
	return 	Cast<UQA_GameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

