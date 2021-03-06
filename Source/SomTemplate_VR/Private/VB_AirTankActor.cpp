// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.
//Written by Jun Zhang, May 2019
#include "VB_AirTankActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

//FRotator test = firstPointer->GetComponentRotation();
	//FString AAA = test.ToString();
	//const TCHAR* BBB = *AAA;
	//UE_LOG(LogTemp, Log, TEXT("Test =================================================== %s"), BBB);

AVB_AirTankActor::AVB_AirTankActor() {
	PrimaryActorTick.bCanEverTick = false;

	m_isFirstKnobOn = false;
	m_isSecondKnobOn = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_AirtankMesh(TEXT("StaticMesh'/Game/Models/EthaneTank.EthaneTank'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FirstKnobMesh(TEXT("StaticMesh'/Game/Models/EthaneKnob.EthaneKnob'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SecondKnobMesh(TEXT("StaticMesh'/Game/Models/EthaneKnob_02.EthaneKnob_02'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PointerMesh(TEXT("StaticMesh'/Game/Models/EthanePointer.EthanePointer'"));
	//Main Airtank Mesh
	if (SM_AirtankMesh.Succeeded()) {
		meshComp->SetStaticMesh(SM_AirtankMesh.Object);
	}
	//First Knob Mesh
	firstKnob = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstKnobComp"));
	firstKnob->SetGenerateOverlapEvents(false);
	firstKnob->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	firstKnob->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	firstKnob->SetupAttachment(meshComp);
	firstKnob->SetRelativeLocation(FVector(0.0f, 0.0f, 46.0f));
	if (SM_FirstKnobMesh.Succeeded()) {
		firstKnob->SetStaticMesh(SM_FirstKnobMesh.Object);
	}
	//We reuse shapeComp and bind it to our first knob
	shapeComp->DestroyComponent();
	shapeComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MainCollisionBox"));
	shapeComp->SetGenerateOverlapEvents(true);
	shapeComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	shapeComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	shapeComp->SetupAttachment(firstKnob);
	shapeComp->SetRelativeLocation(FVector(0.0f, 0.0f, 2.0f));
	Cast<UCapsuleComponent>(shapeComp)->SetCapsuleSize(3.5f, 3.5f);

	//Second Knob
	secondKnob = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondKnobMesh"));
	secondKnob->SetGenerateOverlapEvents(false);
	secondKnob->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	secondKnob->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	secondKnob->SetupAttachment(meshComp);
	secondKnob->SetRelativeLocationAndRotation(FVector(-25.21f, -1.248f, 41.682f), FRotator(0.0f, 0.0f, -120.0f));
	if (SM_SecondKnobMesh.Succeeded()) {
		secondKnob->SetStaticMesh(SM_SecondKnobMesh.Object);
	}
	secondKnobCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SecondKnobCollisionComponent"));
	secondKnobCollisionComp->SetGenerateOverlapEvents(true);
	secondKnobCollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	secondKnobCollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	secondKnobCollisionComp->SetupAttachment(secondKnob);
	secondKnobCollisionComp->SetRelativeLocation(FVector(0.0f, -0.04f, 3.26f));
	secondKnobCollisionComp->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	Cast<UCapsuleComponent>(secondKnobCollisionComp)->SetCapsuleSize(1.8f, 1.8f);

	//First pointer mesh
	firstPointer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pointer_01"));
	firstPointer->SetGenerateOverlapEvents(false);
	firstPointer->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	firstPointer->SetupAttachment(meshComp);
	firstPointer->SetRelativeLocationAndRotation(FVector(-12.653f, -4.8575f, 54.3f), FRotator(55.0f, -133.1f, -127.52f));

	

	//Second pointer mesh
	secondPointer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pointer_02"));
	secondPointer->SetGenerateOverlapEvents(false);
	secondPointer->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	secondPointer->SetupAttachment(meshComp);
	secondPointer->SetRelativeLocationAndRotation(FVector(-26.30f, -3.678f, 51.83f), FRotator(12.839f, -172.94f, -150.13f));
	if (SM_PointerMesh.Succeeded()) {
		firstPointer->SetStaticMesh(SM_PointerMesh.Object);
		secondPointer->SetStaticMesh(SM_PointerMesh.Object);
	}
}

void AVB_AirTankActor::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

	//firstPointer->AddLocalRotation(FRotator(-1.0f, 0.0f, 0.0f));
	//secondPointer->AddLocalRotation(FRotator(-1.0f, 0.0f, 0.0f));
}
 