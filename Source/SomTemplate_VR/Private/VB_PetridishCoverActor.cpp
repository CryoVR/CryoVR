// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "VB_PetridishCoverActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "VB_PetridishActor.h"
#include "VB_StaticActor.h"
#include "VB_LevelScriptActor.h"
#include "Materials/MaterialInstanceConstant.h"
#include "VirtualReality/TP_MotionController.h"

AVB_PetridishCoverActor::AVB_PetridishCoverActor() {
	
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PetridishCover(TEXT("StaticMesh'/Game/Models/GridHolderUMesh.GridHolderUMesh'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI_GlassMatInst(TEXT("MaterialInstanceConstant'/Game/Models/01GridHolderMat_Inst.01GridHolderMat_Inst'"));

	if (SM_PetridishCover.Succeeded()) {
		PickupMesh->SetStaticMesh(SM_PetridishCover.Object);
	}
	if (MI_GlassMatInst.Succeeded()) {
		PickupMesh->SetMaterial(0, MI_GlassMatInst.Object);
	}

	PickupMesh->SetSimulatePhysics(true);
	PickupMesh->SetGenerateOverlapEvents(false);

	covercollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	covercollisionComp->SetupAttachment(PickupMesh);
	covercollisionComp->SetBoxExtent(FVector(4.5f, 4.5f, 1.0f));
	covercollisionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.5f));
	covercollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AVB_PetridishCoverActor::OnOverlapBegin);
	covercollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AVB_PetridishCoverActor::OnHandOverlapBegin);
	covercollisionComp->OnComponentEndOverlap.AddDynamic(this, &AVB_PetridishCoverActor::OnOverlapEnd);

}


void AVB_PetridishCoverActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{ 
	AVB_PetridishActor* petridishActor = Cast<AVB_PetridishActor>(OtherActor);

	if (petridishActor != nullptr) {
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
		PickupMesh->SetSimulatePhysics(false);
		GetRootComponent()->AttachToComponent(OtherActor->GetRootComponent(), AttachRules, FName("UpperCoverSocket"));
		petridishActor->setState(false);
	}
}

void AVB_PetridishCoverActor::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AVB_PetridishActor* petridishActor = Cast<AVB_PetridishActor>(OtherActor);
	if (petridishActor != nullptr) {
		petridishActor->setState(true);
	}
}

void AVB_PetridishCoverActor::OnHandOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ATP_MotionController>(OtherActor)) {
		UpdateHandGuestureFunc(true, FName("Petridish_Socket"), EAttachmentRule::SnapToTarget, FVector(1.0f), TArray<float> {0.3f, 1.0f}, Cast<ATP_MotionController>(OtherActor));
	}
}

void AVB_PetridishCoverActor::Tick(float DeltaTime)
{
	AVB_LevelScriptActor* LSA = Cast<AVB_LevelScriptActor>(GetWorld()->GetLevelScriptActor());

	if (m_isGrab == true)
	{
		if (LSA->GetStatus() == 11)
		{
			LSA->SetStatus(12);
		}
	}
}