// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "VB_TweezerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "VB_PetridishActor.h"
#include "VB_PetridishCoverActor.h"
#include "VB_StaticActor.h"
#include "VB_WorkstationActor.h"
#include "VirtualReality/TP_MotionController.h"
#include "VB_LevelScriptActor.h"
#include "VB_VitrobotActor.h"


// Sets default values
AVB_TweezerActor::AVB_TweezerActor()
{	
	PrimaryActorTick.bCanEverTick = true;
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	capsuleComp->SetGenerateOverlapEvents(true);
	capsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	capsuleComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	capsuleComp->SetCapsuleSize(0.2f, 0.2f);
	capsuleComp->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
	capsuleComp->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	capsuleComp->SetupAttachment(PickupMesh);
	capsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AVB_TweezerActor::OnOverlapBegin);

	tweezerMainCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MainComp"));
	tweezerMainCapsuleComp->SetGenerateOverlapEvents(true);
	tweezerMainCapsuleComp->SetGenerateOverlapEvents(ECollisionEnabled::QueryOnly);
	tweezerMainCapsuleComp->SetCapsuleSize(0.4f, 5.7f);
	tweezerMainCapsuleComp->SetRelativeLocation(FVector(0.0f, 0.0f, -5.19f));
	tweezerMainCapsuleComp->SetupAttachment(PickupMesh);
	tweezerMainCapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AVB_TweezerActor::OnTweezerBeginOverlap);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Tweezer(TEXT("StaticMesh'/Game/Test_Geometry/Test_Textures/Tweezer.Tweezer'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Tweezer_Grid(TEXT("StaticMesh'/Game/Models/Tweezer_Grid.Tweezer_Grid'"));

	if (SM_Tweezer.Succeeded()) {
		PickupMesh->SetStaticMesh(SM_Tweezer.Object);
	}
	PickupMesh->SetGenerateOverlapEvents(false);

	tweezer_grid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tweezer_grid"));
	tweezer_grid->SetGenerateOverlapEvents(false);
	tweezer_grid->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	tweezer_grid->SetVisibility(false);
	tweezer_grid->SetRelativeLocation(FVector(0.0f, 0.0f, -10.92f));
	tweezer_grid->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	tweezer_grid->SetupAttachment(PickupMesh);

	if (SM_Tweezer_Grid.Succeeded()) {
		tweezer_grid->SetStaticMesh(SM_Tweezer_Grid.Object);
	}
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AVB_TweezerActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{	
	AVB_LevelScriptActor* LSA = Cast<AVB_LevelScriptActor>(GetWorld()->GetLevelScriptActor());
	AVB_PetridishActor* petridishActor = Cast<AVB_PetridishActor>(OtherActor);
	if (petridishActor != nullptr && petridishActor->getState()) {
		if (petridishActor->GetGrid() == OtherComp->GetAttachParent()) {
			petridishActor->GetGrid()->SetVisibility(false);
			tweezer_grid->SetVisibility(true);
			AVB_LevelScriptActor* LSA = Cast<AVB_LevelScriptActor>(GetWorld()->GetLevelScriptActor());
			if (LSA != nullptr)
			{
				if (LSA->GetStatus() == 13)
				{
					LSA->SetStatus(14);
				}
			}
			if (!m_isGridAttached) {
				m_isGridAttached = true;
			}
		}
	}
}

void AVB_TweezerActor::OnTweezerBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{	
	ATP_MotionController* MTC = Cast<ATP_MotionController>(OtherActor);
	if (Cast<ATP_MotionController>(OtherActor)) {
		UpdateHandGuestureFunc(true, FName("Tweezer_Socket"), EAttachmentRule::SnapToTarget, FVector(1.0f), TArray<float> {0.0f, 0.5f}, Cast<ATP_MotionController>(OtherActor));
		AVB_LevelScriptActor* LSA = Cast<AVB_LevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (LSA != nullptr)
		{
			if (LSA->GetStatus() == 12)
			{
				LSA->SetStatus(13);
			}
			if (LSA->GetStatus() == 24)
			{	
				
				LSA->SetStatus(25);
			}

		}
	}
	AVB_VitrobotActor* VitrobotActor = Cast<AVB_VitrobotActor>(OtherActor);
	if (VitrobotActor != nullptr) {
		if (m_isGridAttached) {
			FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
			GetRootComponent()->AttachToComponent(VitrobotActor->Plunger, AttachRules, FName("Plunger_Socket_T"));
			AVB_LevelScriptActor* LSA = Cast<AVB_LevelScriptActor>(GetWorld()->GetLevelScriptActor());
			if (LSA != nullptr)
			{
				if (LSA->GetStatus() == 14)
				{
					LSA->SetStatus(15);
				}
			}
		}
	}
}

void AVB_TweezerActor::Tick(float DeltaTime)
{
	AVB_LevelScriptActor* LSA = Cast<AVB_LevelScriptActor>(GetWorld()->GetLevelScriptActor());

	if (m_isGrab == true)
	{
		if (LSA->GetStatus() == 24)
		{
			LSA->SetStatus(25);
		}
	}

	if(LSA->GetStatus() == 26)
	{
		tweezer_grid->SetVisibility(false);
	}
}
