#include "FirstPersonCharacter.h"

#include "Interact/QG_Pickup.h"
#include "Grabber.h"
#include "QG_GameModeBase.h"
#include "QG_GlobalDefines.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

AFirstPersonCharacter::AFirstPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Reach = 250.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));
	Grabber->SetupAttachment(Camera);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandleComponent"));
	PhysicsHandle->LinearDamping = 20.f;
	PhysicsHandle->LinearStiffness = 35.f;
	PhysicsHandle->AngularDamping = 20.f;
	PhysicsHandle->AngularStiffness = 35.f;
}

void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	Inventory.SetNum(4);
	CurrentInteractable = nullptr;
	CacheGameMode();
}

void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//CheckForInteractables();
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("QG_Forward"), this, &AFirstPersonCharacter::Forward);
	PlayerInputComponent->BindAxis(TEXT("QG_Right"), this, &AFirstPersonCharacter::Right);
	PlayerInputComponent->BindAxis(TEXT("QG_LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("QG_LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("QG_Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("QG_Grab"), EInputEvent::IE_Pressed, this, &AFirstPersonCharacter::Grab);
	PlayerInputComponent->BindAction(TEXT("QG_Grab"), EInputEvent::IE_Released, this, &AFirstPersonCharacter::Release);
	PlayerInputComponent->BindAction(TEXT("QG_Pickup"), EInputEvent::IE_Pressed, this, &AFirstPersonCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("QG_Pickup"), EInputEvent::IE_Released, this, &AFirstPersonCharacter::Interact);
	PlayerInputComponent->BindAction(TEXT("QG_Inventory"), EInputEvent::IE_Pressed, this, &AFirstPersonCharacter::ToggleInventoryOn);
	PlayerInputComponent->BindAction(TEXT("QG_Inventory"), EInputEvent::IE_Released, this, &AFirstPersonCharacter::ToggleInventoryOff);
}

void AFirstPersonCharacter::Forward(float AxisValue)
{
	GetCharacterMovement()->AddInputVector(GetActorForwardVector() * AxisValue);
}

void AFirstPersonCharacter::Right(float AxisValue)
{
	GetCharacterMovement()->AddInputVector(GetActorRightVector() * AxisValue);
}

void AFirstPersonCharacter::Grab()
{
	GetGrabber()->Grab();
}

void AFirstPersonCharacter::Release()
{
	GetGrabber()->Release();
}

void AFirstPersonCharacter::ToggleInventoryOn()
{
	if (AQG_GameMode->GetHUDState() == EHUDState::HS_Ingame)
	{
		AQG_GameMode->ChangeHUDState(EHUDState::HS_Inventory);
		bToggleInventoryActive = true;
	}
	else
	{
		AQG_GameMode->ChangeHUDState(EHUDState::HS_Ingame);
	}
}

void AFirstPersonCharacter::ToggleInventoryOff()
{
	/* stub function
	currently do nothing which maskes inventory stay after releaseing I key.
	prevents bug where clicking an item slot toggled inventory off when  BindAction(TEXT("Inventory"), EInputEvent::IE_Released was binded to ToggleInventoryOn()
	might use this in the future
	*/
}

void AFirstPersonCharacter::Interact()
{
	CheckForInteractables();
	if (CurrentInteractable != nullptr)
	{
		CurrentInteractable->Interact_Implementation();
	}
}

void AFirstPersonCharacter::CheckForInteractables()
{
	//Tolinetrace, get the start and end traces from camera location
	FVector Loc;
	FRotator Rot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Loc,Rot);
	FVector StartTrace = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	FVector EndTrace = (Rot.Vector() * Reach) + StartTrace;

	// DEBUG line
	//UKismetSystemLibrary::DrawDebugLine(this, StartTrace,EndTrace,FLinearColor::Red,5.f,5.f);

	FHitResult HitResult;

	//Initialize the query params - ignore this actor to avoid trace stop on self
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(HitResult,StartTrace,EndTrace,ECC_WorldDynamic,CQP);
	AQG_Interactable* PotentialInteractable = Cast<AQG_Interactable>(HitResult.Actor);

	if (PotentialInteractable == nullptr)
	{
		HelpText = FString(" ");
		CurrentInteractable = nullptr;
	}
	else
	{
		CurrentInteractable = PotentialInteractable;
		HelpText = CurrentInteractable->InteractableHelpText;
	}
}

void AFirstPersonCharacter::UpdateGold(int32 Amount)
{
	Gold += Amount;
}

bool AFirstPersonCharacter::AddItemToInventory(AQG_Pickup* Item)
{
	if (Item != nullptr)
	{
		const int32 AvaibleSlot = Inventory.Find(nullptr);
		if (AvaibleSlot != INDEX_NONE)
		{
			Inventory[AvaibleSlot] = Item;
			return true;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,TEXT("You cant carry any more items!"));
			return false;
		}
	}
	else return false;
}

UTexture2D* AFirstPersonCharacter::GetThumbnailAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot]  != NULL)
	{
		return Inventory[Slot]->GetPickupThumbnail();
	}
	return nullptr;
}

FString AFirstPersonCharacter::GetItemNameAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		return Inventory[Slot]->GetItemName();
	}
	return FString("None");
}

void AFirstPersonCharacter::UseItemAtInventorySlot(int32 Slot)
{
	if (Inventory[Slot] != NULL)
	{
		Inventory[Slot]->Use_Implementation();
		Inventory[Slot] = NULL;
		AQG_GameMode->SetHUDState(EHUDState::HS_Inventory);
	}
}

void AFirstPersonCharacter::CacheGameMode()
{
	if (AQG_GameMode != nullptr) return;

	AQG_GameMode = Cast<AQG_GameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!AQG_GameMode) {
		UE_LOG(XXXXX_Log_QG, Error, TEXT("@@@@@ [%s] CacheGameMode() at begin play failed, no GM found "), *this->GetName());
	}
}
