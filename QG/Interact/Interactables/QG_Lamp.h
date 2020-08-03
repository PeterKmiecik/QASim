#pragma once

#include "CoreMinimal.h"
#include "Interact/QG_Interactable.h"
#include "QG_Lamp.generated.h"

UCLASS()
class QG_API AQG_Lamp : public AQG_Interactable
{
	GENERATED_BODY()
public:
	AQG_Lamp();
	void ToggleLight();
	virtual void Interact_Implementation() override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|QG_Lamp")
	class UStaticMeshComponent* LampMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|QG_Lamp")
	class UPointLightComponent* LampLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|QG_Lamp")
	class UMaterialInstanceDynamic* LampMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|QG_Lamp")
	class AQG_LightSwitchSlot* LightSwitchSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "@@@ QG|QG_Lamp")
	float LampMaterialEmissiveGlow = 0.f;
};
