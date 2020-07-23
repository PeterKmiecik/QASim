#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void BeginPlay() override;
	
	void LaunchProjectile(float Speed);

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|Projectile")
	float DestroyDelay = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "@@@ BT|Projectile")
	float ProjectileDamage = 20.f;

	class UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Projectile")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Projectile")
	class UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Projectile")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "@@@ BT|Projectile")
	class URadialForceComponent* ExplosionForce = nullptr;
};
