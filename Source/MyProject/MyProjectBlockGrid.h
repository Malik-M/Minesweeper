// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectBlockGrid.generated.h"

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class AMyProjectBlockGrid : public AActor
{
	GENERATED_BODY()

		/** Dummy root component */
		UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UTextRenderComponent* ScoreText;

public:
	AMyProjectBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;



	/** Number of blocks along each side of grid */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		int32 Size;

	/** array that holds all of the boxes */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		TArray<AMyProjectBlock*> BoxGrid;

	/** Spacing of blocks */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float BlockSpacing;

	/** Num of Bombs */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		int32 BombNum;

	UFUNCTION()
	int GetAmountOfBombs(AMyProjectBlock* curentBlock);

	int BombCounter(FString location, AMyProjectBlock* curentBlock);

	void ZeroClearer(AMyProjectBlock* curentBlock);

	int LocationInArray(AMyProjectBlock* curentBlock);

	FString GetLocation(int temp);



protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Handle bomb Click */
	void GameOver();



	/** Handle the block being clicked */
	void AddScore();

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
};



