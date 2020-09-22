// Peter Kmiecik Art All Rights Reserved
#include "RPS_MainGameWidget.h"
#include "BPFL_Global.h"

#include "Private/RPS_GameMode.h"

#include "Animation/WidgetAnimation.h"

URPS_MainGameWidget::URPS_MainGameWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerShapesButtonsBox = nullptr;
}

bool URPS_MainGameWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	UE_LOG(XXXXX_Log_RPS, Log, TEXT("@@@ [%s] MAIN GAME WIDGET Initialize() "), *this->GetName());

	Init();

	return true;
}

void URPS_MainGameWidget::Init()
{
	if (Scissors2DTexture && Rock2DTexture && Paper2DTexture)
	{
		UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [%s] Textures2D references of shapes not set in BP ! "), *this->GetName());
		return;
	}

}

UHorizontalBox* URPS_MainGameWidget::GetPlayerShapesButtonsBox() const
{
	if (!PlayerShapesButtonsBox)
	{
		UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [%s] GetPlayerShapesButtonsBox() variable GetPlayerShapesButtonsBox is not valid. Check BPs widget for correct naming of widget on CanvasPanel"), *this->GetName());
		return nullptr;
	}
	 return PlayerShapesButtonsBox; 
}

UImage* URPS_MainGameWidget::GetPlayerHandImage()
{
	if (!PlayerHandImage)
	{
		UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [%s] GetPlayerHandImage() variable PlayerHandImage is not valid. Check BPs widget for correct naming of widget on CanvasPanel"), *this->GetName());
		return nullptr;
	}
	return PlayerHandImage;
}

UImage* URPS_MainGameWidget::GetCpuHandImage()
{
	if (!CpuHandImage)
	{
		UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [%s] GetCpuHandImage() variable PlayerHandImage is not valid. Check BPs widget for correct naming of widget on CanvasPanel"), *this->GetName());
		return nullptr;
	}
	return CpuHandImage;
}

UTexture2D* URPS_MainGameWidget::GetPlayableShape2DTexture(EPlayableShape ShapeType)
{
	UTexture2D* Local2DTexture = Rock2DTexture;
	switch (ShapeType)
	{
	case EPlayableShape::EPS_Rock:
		Local2DTexture = Rock2DTexture;
		break;
	case EPlayableShape::EPS_Paper:
		Local2DTexture = Paper2DTexture;
		break;
	case EPlayableShape::EPS_Scissors:
		Local2DTexture = Scissors2DTexture;
		break;
	case EPlayableShape::EPS_null:
		break;
	default:
		break;
	}

	return Local2DTexture;
}

void URPS_MainGameWidget::PlayAttackAnimation(UWidgetAnimation* InWidgetObjectAnimation)
{
	PlayAnimation(InWidgetObjectAnimation);
}

UWidgetAnimation* URPS_MainGameWidget::GetAttackAnimation()
{
	if (!AttackAnimation)
	{
		UE_LOG(XXXXX_Log_RPS, Error, TEXT("@@@ [%s] GetAttackAnimation() variable AttackAnimation is not valid. Check BPs widget for correct naming of widget on CanvasPanel"), *this->GetName());
		return nullptr;
	}
	return AttackAnimation;
}
