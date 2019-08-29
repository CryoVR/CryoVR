// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VB_DynamicActor.h"
#include "VB_PenActor.generated.h"

/**
 * 
 */
class UCapsuleComponent;

UCLASS()
class SOMTEMPLATE_VR_API AVB_PenActor : public AVB_DynamicActor
{
	GENERATED_BODY()
	
public:
	AVB_PenActor();

protected:
		UPROPERTY(VisibleAnywhere, Category = "Components")
		UCapsuleComponent* Pointer_Collider;
};
