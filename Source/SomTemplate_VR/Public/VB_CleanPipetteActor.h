// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VB_DynamicActor.h"
#include "VB_CleanPipetteActor.generated.h"

/**
 * 
 */

class UCapsuleComponent;

UCLASS()
class SOMTEMPLATE_VR_API AVB_CleanPipetteActor : public AVB_DynamicActor
{
	GENERATED_BODY()

public:
	AVB_CleanPipetteActor();

	UPROPERTY(BlueprintReadWrite)
	bool bIsOnTable;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnPipetHandOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UCapsuleComponent* HandcapsuleComp;
};
