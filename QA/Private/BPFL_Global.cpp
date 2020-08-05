// Peter Kmiecik Art All Rights Reserved


#include "BPFL_Global.h"
#include "QA/Private/UI/QAUserWidget.h"


DEFINE_LOG_CATEGORY(XXXX_Log_QA);
DEFINE_LOG_CATEGORY(XXXXX_Log_SHMUP);

// https://youtu.be/vi3ZRD5VcgI?list=PLZlv_N0_O1gaz3ydgU5wt6c_JtJzwXUKW&t=4296

float UBPFL_Global::DotToTarget(AActor* FromActor, AActor* TargetActor, FString WhereItWasCalledFromErrorMsg)
{
	if (!FromActor) {
		UE_LOG(XXXX_Log_QA, Warning, TEXT("@@@ [QA] [BPFL_Global] function called from [%s]: DotToTarget() parameter: FromActor passed was nullptr"), *WhereItWasCalledFromErrorMsg);
		return -2.f;}
	if (!TargetActor) {
		UE_LOG(XXXX_Log_QA, Warning, TEXT("@@@ [QA] [BPFL_Global] function called from [%s]: DotToTarget() parameter: TargetActor passed was nullptr"), *WhereItWasCalledFromErrorMsg);
		return -2.f;}
	FVector FromActorLocation = FromActor->GetActorLocation();
	FVector DirectionToTarget = (TargetActor->GetActorLocation() - FromActorLocation).GetSafeNormal2D();
	return FVector::DotProduct(FromActor->GetActorForwardVector(), DirectionToTarget);
}
