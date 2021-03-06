// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.
//Written by Jun Zhang & Jiahui Dong, May 2019
#pragma once

#include "CoreMinimal.h"
#include "VB_StaticActor.h"
#include "VirtualReality/TP_PickupCube.h"
#include "VB_DynamicActor.generated.h"


/**
 * 
 */
UCLASS()
class SOMTEMPLATE_VR_API AVB_DynamicActor : public ATP_PickupCube
{
	GENERATED_BODY()
public:
	//Set default
	AVB_DynamicActor();
	//Pick up interface
	virtual void Pickup_Implementation(class USceneComponent* AttachTo);
	//Drop interface
	virtual void Drop_Implementation();

	virtual void BeginPlay() override;

	//virtual void Tick(float DeltaTime) override;

	//Set whether the object is pickable or not
	void setPickable(bool newPickable);
	bool getPickable();

	//Return child component by id (level), default is 0, means root component
	virtual USceneComponent* GetComponentByIndex(int compIndex = 0);

	void OnHitGround(float resetTransformTimer);

	//Reset Actor to original position and state
	UFUNCTION()
	virtual void ResetActorState();

	//Indicate whether this object is picked up #default, false
	bool m_isGrab;


protected:
	//Define whether this object can be picked up
	UPROPERTY(EditInstanceOnly, Category = "Behavior")
	bool m_isPickable;
	//Set actor original position, rotation and scale
	FTransform m_OriginalTransform;
	//Time Handler
	FTimerHandle timeHandler;
	
};
