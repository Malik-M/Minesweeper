// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyProjectBlock.h"
#include "MyProjectBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/TextRenderComponent.h"
#include "Engine/Engine.h"
#include "Components/InputComponent.h"
#include "Materials/MaterialInstance.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

AMyProjectBlock::AMyProjectBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RedMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GreenMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
			, RedMaterial(TEXT("/Game/Puzzle/Meshes/RedMaterial.RedMaterial"))
			, GreenMaterial(TEXT("/Game/Puzzle/Meshes/GreenMaterial.GreenMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(.5f, .5f, 0.125f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AMyProjectBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AMyProjectBlock::OnFingerPressedBlock);
	//just made left click and flagged didnt test
	
	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
	RedMaterial = ConstructorStatics.RedMaterial.Get();
	GreenMaterial = ConstructorStatics.GreenMaterial.Get();

	//Text for each Block
	BlockText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BlockText0"));
	BlockText->SetText((""));
	BlockText->SetRelativeLocation(FVector(-10.f, 0.f, 50.f));
	BlockText->SetRelativeRotation(FRotator(90.f, 0.f, 180.f));
	BlockText->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	BlockText->SetupAttachment(DummyRoot);
}

void AMyProjectBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	if (ButtonClicked.ToString() == "LeftMouseButton")
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, ButtonClicked.ToString());

	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("RightMouseButton")));
	}
	
	HandleClicked();
}


void AMyProjectBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("RightMouseButton")));
	HandleClicked();
}





void AMyProjectBlock::OnRightClick(ETouchIndex::Type FingerMiddle, UPrimitiveComponent* TouchedComponent)
{

}

void AMyProjectBlock::HandleClicked()
{
	// Check we are not Bomb
	if (!bIsBomb && !bIsActive){
		bIsActive = true;

		//see how many blocks are around this block is a bomb
		int numOfBombs = OwningGrid->GetAmountOfBombs(this);

		// Change material
		BlockMesh->SetMaterial(0, OrangeMaterial);

		//see if the current block is 0
		if (numOfBombs == 0) {
			OwningGrid->ZeroClearer(this);

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Zero Called")));
		}

		//Sets the text to the amount of bombs in this blocks area
		BlockText->SetText(FText::Format(LOCTEXT("ScoreFmt", "{0}"), FText::AsNumber(numOfBombs)));

		// Tell the Grid
		if (OwningGrid != nullptr)
		{
			OwningGrid->AddScore();
		}

	}
	if (bIsBomb) {
		bIsActive = true;
		BlockMesh->SetMaterial(0, RedMaterial);

		if (OwningGrid != nullptr)
		{
			OwningGrid->GameOver();
		}
	}
}

void AMyProjectBlock::SetToRed()
{
	BlockMesh->SetMaterial(0, RedMaterial);
	bIsActive = true;
}

void AMyProjectBlock::Flag() {
	bool bflagged = this->bIsFlagged;
	if (bflagged){
		this->bIsFlagged = false;
		BlockText->SetText((""));
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
	else{
		this->bIsFlagged = true;
		BlockText->SetText(("?"));
		BlockMesh->SetMaterial(0, GreenMaterial);
	}
}

void AMyProjectBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (bIsActive)
	{
		return;
	}
	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
}


