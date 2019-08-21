// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "VB_GridBoxTweezerActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "VB_WorkstationActor.h"
#include "VB_GridTubeActor.h"
#include "VB_StaticActor.h"
#include "VirtualReality/TP_MotionController.h"
#include "VB_VitrobotActor.h"

AVB_GridBoxTweezerActor::AVB_GridBoxTweezerActor()
{
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	capsuleComp->SetGenerateOverlapEvents(true);
	capsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	capsuleComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	capsuleComp->SetCapsuleSize(0.2f, 0.2f);
	capsuleComp->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
	capsuleComp->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	capsuleComp->SetupAttachment(PickupMesh);
	capsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AVB_GridBoxTweezerActor::OnOverlapBegin);

	tweezerMainCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MainComp"));
	tweezerMainCapsuleComp->SetGenerateOverlapEvents(true);
	tweezerMainCapsuleComp->SetGenerateOverlapEvents(ECollisionEnabled::QueryOnly);
	tweezerMainCapsuleComp->SetCapsuleSize(0.4f, 5.7f);
	tweezerMainCapsuleComp->SetRelativeLocation(FVector(0.0f, 0.0f, -5.19f));
	tweezerMainCapsuleComp->SetupAttachment(PickupMesh);
	//tweezerMainCapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AVB_TweezerActor::OnTweezerBeginOverlap);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Tweezer(TEXT("StaticMesh'/Game/Test_Geometry/Test_Textures/Tweezer.Tweezer'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Tweezer_Grid(TEXT("StaticMesh'/Game/Test_Geometry/Test_Textures/Grid_Box.Grid_Box'"));

	if (SM_Tweezer.Succeeded()) {
		PickupMesh->SetStaticMesh(SM_Tweezer.Object);
	}
	PickupMesh->SetGenerateOverlapEvents(false);
	PickupMesh->SetRelativeScale3D(FVector(2.0f));

	tweezer_grid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tweezer_grid"));
	tweezer_grid->SetGenerateOverlapEvents(false);
	tweezer_grid->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	tweezer_grid->SetVisibility(false);
	tweezer_grid->SetRelativeLocation(FVector(0.0f, 0.0f, -10.92f));
	tweezer_grid->SetRelativeScale3D(FVector(1.0f));
	tweezer_grid->SetRelativeRotation(FRotator(90.0f, 180.0f, 0.0f)); 
	tweezer_grid->SetupAttachment(PickupMesh);
	if (SM_Tweezer_Grid.Succeeded()) {
		tweezer_grid->SetStaticMesh(SM_Tweezer_Grid.Object);
	}
}

void AVB_GridBoxTweezerActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AVB_WorkstationActor *WorkstationActor = Cast<AVB_WorkstationActor>(OtherActor);
	if (WorkstationActor != nullptr)
	{
		tweezer_grid->SetVisibility(true);
		UE_LOG(LogTemp, Log, TEXT("hey"));
	}
	AVB_GridTubeActor *GridTubeActor = Cast<AVB_GridTubeActor>(OtherActor);
	if (GridTubeActor != nullptr)
	{
		tweezer_grid->SetVisibility(false);
	}
}