// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VB_DynamicActor.h"
#include "VB_CleanLabGoggleActor.generated.h"

/**
 * 
 */
class UBoxComponent;

UCLASS()
class SOMTEMPLATE_VR_API AVB_CleanLabGoggleActor : public AVB_DynamicActor
{
	GENERATED_BODY()

public:
	AVB_CleanLabGoggleActor();

	bool bIsOnTable;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* BoxComp;

	class ALevelScriptActor* GetLevelScriptActor(class ULevel* OwnerLevel = NULL) const;
};