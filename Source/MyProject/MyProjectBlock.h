// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectBlock.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class AMyProjectBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BlockMesh;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UTextRenderComponent* BlockText;

public:
	AMyProjectBlock();

	/** Are we currently active? */
	bool bIsActive;

	/** Are we A Bomb */
	bool bIsBomb;

	/*is the current block flagged*/
	bool bIsFlagged;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
		class UMaterial* BaseMaterial;

	/** Pointer to blue material used on inactive blocks */
	UPROPERTY()
		class UMaterialInstance* BlueMaterial;

	/** Pointer to orange material used on active non-bomb blocks */
	UPROPERTY()
		class UMaterialInstance* OrangeMaterial;

	/** Pointer to blue material used on active bomb blocks */
	UPROPERTY()
		class UMaterialInstance* RedMaterial;

	/** Pointer to blue material used on Flagged blocks */
	UPROPERTY()
		class UMaterialInstance* GreenMaterial;

	/** Grid that owns us */
	UPROPERTY()
		class AMyProjectBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
		void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
		void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	/** Handle the block being touched  */
	UFUNCTION()
		void OnRightClick(ETouchIndex::Type FingerMiddle, UPrimitiveComponent* TouchedComponent);

	void HandleClicked();

	void Highlight(bool bOn);

	void SetToRed();

	void Flag();

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};





