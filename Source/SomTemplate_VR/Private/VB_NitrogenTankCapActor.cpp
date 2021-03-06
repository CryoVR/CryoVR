// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "VB_NitrogenTankCapActor.h"
#include "Public/Engine.h"
#include "Math/TransformNonVectorized.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VB_DewarActor.h"
#include "TimerManager.h"
#include "VB_LevelScriptActor.h"
#include "VirtualReality/TP_MotionController.h"

AVB_NitrogenTankCapActor::AVB_NitrogenTankCapActor()
{
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	CapsuleComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CapsuleComp->SetRelativeScale3D(FVector(0.08f, 0.14f, 0.09f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_DewarCap(TEXT("StaticMesh'/Game/Models/NitrogenTankCapMesh.NitrogenTankCapMesh'"));
	if (SM_DewarCap.Succeeded())
	{
		UStaticMesh* Asset = SM_DewarCap.Object;
		PickupMesh->SetStaticMesh(Asset);
		PickupMesh->SetSimulatePhysics(true);
		CapsuleComp->SetupAttachment(PickupMesh);
		CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AVB_NitrogenTankCapActor::OnOverlapBegin);

	}
}



void AVB_NitrogenTankCapActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (Cast<AVB_DewarActor>(OtherActor) != nullptr)
	//{
	//	//FName DewarSocket = "CapSocket";
	//	//FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	//	//GetRootComponent()->AttachToComponent(OtherActor->GetRootComponent(), AttachmentTransformRules, DewarSocket);
	//	//PickupMesh->SetSimulatePhysics(false);
	//}

	if (Cast<ATP_MotionController>(OtherActor)) {
		UpdateHandGuestureFunc(true, FName("TankCap_Socket"), EAttachmentRule::SnapToTarget, FVector(1.0f), TArray<float> {0.33f, 0.8f}, Cast<ATP_MotionController>(OtherActor));
		
	}
}

void AVB_NitrogenTankCapActor::Tick(float DeltaTime)
{
	AVB_LevelScriptActor* LSA = Cast<AVB_LevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (LSA != nullptr)
	{
		if (m_isGrab)
		{	
			if (LSA->GetStatus() == 2)
			{
				LSA->SetStatus(3);
			}
			
		}

	}
}


void AVB_NitrogenTankCapActor::ResetActorState() {
	SetActorTransform(m_OriginalTransform);
	PickupMesh->SetWorldLocation(FVector(45.9999161f, 103.0520096f, 160.9748535f));
	PickupMesh->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	PickupMesh->SetSimulatePhysics(true);
}




