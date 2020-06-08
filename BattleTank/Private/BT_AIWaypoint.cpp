// Peter Kmiecik Art All Rights Reserved


#include "BT_AIWaypoint.h"
#include "Components/BillboardComponent.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ABT_AIWaypoint::ABT_AIWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

#if WITH_EDITORONLY_DATA

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
	if (Billboard)
	{
		Billboard->bHiddenInGame = false;
		Billboard->SetupAttachment(RootComponent);
	}
	bHidden = false;


#endif WITH_EDITORONLY_DATA
}

// Called when the game starts or when spawned
void ABT_AIWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABT_AIWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

