// Peter Kmiecik Art All Rights Reserved


#include "SHMUP_BasePawn.h"

// Sets default values
ASHMUP_BasePawn::ASHMUP_BasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASHMUP_BasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASHMUP_BasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASHMUP_BasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASHMUP_BasePawn::Destroyed()
{
	ShipHasDied.Broadcast();
}



