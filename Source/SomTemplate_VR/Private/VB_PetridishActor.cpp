// Copyright (c) 2014-2019 Sombusta, All Rights Reserved.


#include "VB_PetridishActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"

AVB_PetridishActor::AVB_PetridishActor() 
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GridHolderDMesh(TEXT("StaticMesh'/Game/Models/GridHolderDMesh.GridHolderDMesh'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Petridish_Grid(TEXT("StaticMesh'/Game/Models/Tweezer_Grid.Tweezer_Grid'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Petridish_Grid_One(TEXT("StaticMesh'/Game/Models/Tweezer_Grid.Tweezer_Grid'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Petridish_Grid_Two(TEXT("StaticMesh'/Game/Models/Tweezer_Grid.Tweezer_Grid'"));

	if (SM_GridHolderDMesh.Succeeded()) {
		meshComp->SetStaticMesh(SM_GridHolderDMesh.Object);
	}

	//#1 gird
	petridish_grid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petridish_grid"));
	petridish_grid->SetGenerateOverlapEvents(true);
	petridish_grid->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	petridish_grid->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	petridish_grid->SetVisibility(true);
	petridish_grid->SetRelativeLocation(FVector(0.0f, 0.0f, 0.3f));
	petridish_grid->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	petridish_grid->SetupAttachment(meshComp);

	//#2 grid
	petridish_grid_one = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petridish_grid_one"));
	petridish_grid_one->SetGenerateOverlapEvents(true);
	petridish_grid_one->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	petridish_grid_one->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	petridish_grid_one->SetVisibility(true);
	petridish_grid_one->SetRelativeLocation(FVector(1.0f, 1.0f, 0.3f));
	petridish_grid_one->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	petridish_grid_one->SetupAttachment(meshComp);

	//#3 grid
	petridish_grid_two = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Petridish_grid_two"));
	petridish_grid_two->SetGenerateOverlapEvents(true);
	petridish_grid_two->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	petridish_grid_two->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	petridish_grid_two->SetVisibility(true);
	petridish_grid_two->SetRelativeLocation(FVector(-1.0f, 2.0f, 0.3f));
	petridish_grid_two->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	petridish_grid_two->SetupAttachment(meshComp);
	
	if (SM_Petridish_Grid.Succeeded()) {
		petridish_grid->SetStaticMesh(SM_Petridish_Grid.Object);
	}

	if (SM_Petridish_Grid_One.Succeeded()) {
		petridish_grid_one->SetStaticMesh(SM_Petridish_Grid_One.Object);
	}

	if (SM_Petridish_Grid_Two.Succeeded()) {
		petridish_grid_two->SetStaticMesh(SM_Petridish_Grid_Two.Object);
	}

	shapeComp->DestroyComponent();
	shapeComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Petridish"));
	shapeComp->SetGenerateOverlapEvents(true);
	shapeComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	shapeComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Cast<UCapsuleComponent>(shapeComp)->SetCapsuleSize(2.0f, 2.0f);
	shapeComp->SetupAttachment(petridish_grid);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

UStaticMeshComponent * AVB_PetridishActor::GetGrid(int index)
{
	if (index < 0 || index > 2) {
		return NULL;
	}
	else if (index == 0) {
		return petridish_grid;
	}
	else if (index == 1) {
		return petridish_grid_one;
	}
	else {
		return petridish_grid_two;
	}
}