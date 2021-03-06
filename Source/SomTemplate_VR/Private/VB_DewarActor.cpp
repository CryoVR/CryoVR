// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.

//Now it's the test version with the Tick function
#include "VB_DewarActor.h"
#include "Public/Engine.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VB_NitrogenTankCapActor.h"
#include "VB_LevelScriptActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "VirtualReality/TP_MotionController.h"

AVB_DewarActor::AVB_DewarActor()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxCompCap = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompCap"));
	BoxCompCap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCompCap->OnComponentBeginOverlap.AddDynamic(this, &AVB_DewarActor::OnOverlapBegin);
	BoxCompCap->OnComponentEndOverlap.AddDynamic(this, &AVB_DewarActor::OnOverlapEnd);
	BoxCompCap->SetRelativeLocation(FVector(0.0f, 0.0f, 37.05f));
	BoxCompCap->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.04f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Dewar(TEXT("StaticMesh'/Game/Models/DewarMesh.DewarMesh'"));
	if (SM_Dewar.Succeeded())
	{
		UStaticMesh* Asset = SM_Dewar.Object;
		PickupMesh->SetStaticMesh(Asset);
		BoxCompCap->SetupAttachment(PickupMesh);

	}

	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Effect(TEXT("ParticleSystem'/Game/Particles/WaterSplash_P.WaterSplash_P'"));
	if (P_Effect.Succeeded())
	{
		FrozenFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FrozenEffect"));
		FrozenFX->SetGenerateOverlapEvents(false);
		FrozenFX->SetTemplate(P_Effect.Object);
		FrozenFX->SetupAttachment(PickupMesh);
		FrozenFX->SetWorldLocation(FVector(0.0f, 0.0f, 38.0f));
	}
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Effect1(TEXT("ParticleSystem'/Game/Particles/WaterFall.WaterFall'"));
	if (P_Effect1.Succeeded())
	{
		Waterfall = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WaterEffect"));
		Waterfall->SetTemplate(P_Effect1.Object);
		Waterfall->SetGenerateOverlapEvents(false);
		Waterfall->SetupAttachment(PickupMesh);
		Waterfall->SetWorldLocation(FVector(0.0f, 0.0f, 38.0f));
	}

	HandcapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DewarCapsuleComp"));
	HandcapsuleComp->SetGenerateOverlapEvents(true);
	HandcapsuleComp->SetGenerateOverlapEvents(ECollisionEnabled::QueryOnly);
	HandcapsuleComp->SetCapsuleSize(2.5f, 10.0f);
	HandcapsuleComp->SetRelativeLocation(FVector(-10.0f, 0.0f, 20.0f));
	HandcapsuleComp->SetupAttachment(PickupMesh);
	HandcapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AVB_DewarActor::OnHandOverlapBegin);

}

void AVB_DewarActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AVB_NitrogenTankCapActor>(OtherActor) != nullptr && m_Isattached == false)
	{	
		m_Isattached = true;
		FName DewarSocket = "CapSocket";
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
		OtherActor->GetRootComponent()->AttachToComponent(GetRootComponent(), AttachmentTransformRules, DewarSocket);
		FrozenFX->SetActive(false);
		Waterfall->SetActive(false);
	}
}

void AVB_DewarActor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AVB_NitrogenTankCapActor>(OtherActor) != nullptr)
	{
		//OtherActor->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		FrozenFX->SetActive(true);
		Waterfall->SetActive(true);
		m_Isattached = false;
	}
}

void AVB_DewarActor::OnHandOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (Cast<ATP_MotionController>(OtherActor)) {
		UpdateHandGuestureFunc(true, FName("Dewar_Socket"), EAttachmentRule::SnapToTarget, FVector(1.0f), TArray<float> {3.0f, 0.0f}, Cast<ATP_MotionController>(OtherActor));
	}
}

void AVB_DewarActor::Tick(float DeltaTime)
{
	AVB_LevelScriptActor* LSA = Cast<AVB_LevelScriptActor>(GetWorld()->GetLevelScriptActor());

		if (m_isGrab == true)
		{
			if (LSA->GetStatus() == 1)
			{
				LSA->SetStatus(2);
			}
		}
}
