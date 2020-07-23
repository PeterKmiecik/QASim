#include "SpawnPoint.h"
#include "BattleTank.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "SprungWheel.h"

USpawnPoint::USpawnPoint()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnedActor = GetWorld()->SpawnActorDeferred<ASprungWheel>(SpawnClass, GetComponentTransform());
	if (!SpawnedActor) {
		UE_LOG(XXXXX_Log_BT, Warning, TEXT("@@@@@ SpawnedActor is null"));
		return;
	}

	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}

void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

