#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" 

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDrivingForward, float, OutThrow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDrivingSide, float, OutThrow);

/* //  This struct covers all possible tank input schemes. What the inputs do can vary by tank, but not what inputs exist.*/
USTRUCT(BlueprintType)
struct FTankInput
{
	GENERATED_BODY()

public:
	// Sanitized movement input, usable for game logic.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "@@@ BT|Tank|TankMovement")
	FVector2D MovementInput;

	void Sanitize();
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

private:
	//~ Code only. Blueprints should not need to know about this. This should not be used for game logic.
	FVector2D RawMovementInput;
};

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/* // Event fires when player stops pressing input*/
	UFUNCTION(BlueprintImplementableEvent, Category = "@@@ BT|Tank|Input")
	void OnFwdBckwrdMovementStop();

	/* // Event fires when player stops pressing input*/
	UFUNCTION(BlueprintImplementableEvent, Category = "@@@ BT|Tank|Input")
	void OnLeftRightStop();

	/* // Multicast delegate */
	UPROPERTY(BlueprintAssignable, Category = "@@@ BT|Tank|Input")
	FOnDrivingForward OnDrivingForward;

	/* // Multicast delegate */
	UPROPERTY(BlueprintAssignable, Category = "@@@ BT|Tank|Input")
	FOnDrivingSide OnDrivingSide;
	
	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank|Input")
	FORCEINLINE FTankInput GetCurrentInput() const { return TankInput; }

	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "@@@ BT|Tank")
	 float GetHealthPercent() const;

	FTankDelegate OnDeath;

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank")
	FORCEINLINE ATank* GetTankRef() { return this; }

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void LookUp(float Value);

	UFUNCTION()
	void Turn(float Value);

	UFUNCTION()
	void DriveForwardBackward(float Value);

	UFUNCTION()
	void TurnRightLeft(float Value);

	/* 	// Zeroing Turret rotation casued by tank rotation */
	UFUNCTION()
	void StabilizeTurretYaw(float Throw);

	void EnginePitchHandler();

	FORCEINLINE float GetWheelLinearDampingToStop() { return WheelLinearDampingToStop; }
	FORCEINLINE float GetWheelAngularDampingToStop() { return WheelAngularDampingToStop; }
	FORCEINLINE float GetTankLinearDampingToStop() { return TankLinearDampingToStop; }
	FORCEINLINE float GetTankAngularDampingToStop() { return TankAngularDampingToStop; }

	FORCEINLINE float GetWheelLinearDampingDriving() { return WheelLinearDampingDriving; }
	FORCEINLINE float GetWheelAngularDampingDriving() { return WheelAngularDampingDriving; }
	FORCEINLINE float GetTankLinearDampingDriving() { return TankLinearDampingDriving; }
	FORCEINLINE float GetTankAngularDampingDriving() { return TankAngularDampingDriving; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "@@@ BT|Tank")
	class UTankAimingComponent* TankAimingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "@@@ BT|Tank")
	class UTankMovementComponent* TankMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "@@@ BT|Tank")
	class USoundBase* EngineSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "@@@ BT|Tank")
	float LowEnginePitch = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "@@@ BT|Tank")
	float HighEnginePitch = 2.f;

	UFUNCTION(BlueprintCallable, Category = "@@@ BT|Tank")
	void Init();

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ BT|Tank|Movement")
	bool bDrivngForward;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ BT|Tank|Movement")
	bool bTurning;

	virtual void Tick(float DeltaTime) override;
private:
	ATank();

	// Current input for our tank. Sanitized in Tick().
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ BT|Tank|Input")
	FTankInput TankInput;

	FRotator TankRotationBeforeInput;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|Tank")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Tank")
	int32 CurrentHealth; 

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"), Category = "@@@ BT|Tank|Movement|TankTrack")
	float WheelLinearDampingToStop = 1000.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"), Category = "@@@ BT|Tank|Movement|TankTrack")
	float WheelAngularDampingToStop = 1000.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"), Category = "@@@ BT|Tank|Movement|TankTrack")
	float WheelAngularDampingDriving = 1000.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"), Category = "@@@ BT|Tank|Movement|TankTrack")
	float WheelLinearDampingDriving = 10.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"), Category = "@@@ BT|Tank|Movement")
	float TankLinearDampingToStop = 1000.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"), Category = "@@@ BT|Tank|Movement")
	float TankAngularDampingToStop = 1000.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"), Category = "@@@ BT|Tank|Movement")
	float TankAngularDampingDriving = 0.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"), Category = "@@@ BT|Tank|Movement")
	float TankLinearDampingDriving = 0.f;

	void SetupEngineSounds(USoundBase* Sound);

	class UAudioComponent* TankEngineAudioComp;

};
