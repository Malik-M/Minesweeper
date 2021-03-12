// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyProjectBlockGrid.h"
#include "MyProjectBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

AMyProjectBlockGrid::AMyProjectBlockGrid()
{
	// Set defaults
	Size = 8;
	BlockSpacing = 150.f;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(100.f, 500.f, 0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);


}




void AMyProjectBlockGrid::BeginPlay()
{
	Super::BeginPlay();
	
	// Number of blocks
	const int32 NumBlocks = Size * Size;
	
	//testing
	BoxGrid.Reserve(NumBlocks);

	int32 bombLocations[7];
	for (int32 i = 0; i < 7; i++){
		bombLocations[i] = FMath::RandRange(0, NumBlocks);
	}

	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumBlocks; BlockIndex++) {
		
		const float XOffset = (BlockIndex / Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex % Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		AMyProjectBlock* NewBlock = GetWorld()->SpawnActor<AMyProjectBlock>(BlockLocation, FRotator(0, 0, 0));
		
		//generates random Bombs
		for (int32 i = 0; i < 7; i++) {
			if (bombLocations[i] == BlockIndex) {
				NewBlock->bIsBomb = true;
			}
		}
		
		//Set the flagged to false
		NewBlock->bIsFlagged = false;

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}

		// Add it to the box array
		BoxGrid.Add((NewBlock));
	}

}


int AMyProjectBlockGrid::GetAmountOfBombs(AMyProjectBlock* curentBlock)
{
	//Number of bombs Found
	int counter = 0;

	counter = counter + BombCounter(GetLocation(LocationInArray(curentBlock)), curentBlock);

	//if (GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("total bombs: %lld"), counter));}

	return counter;
}
 
int AMyProjectBlockGrid::BombCounter(FString location, AMyProjectBlock* curentBlock)
{// todo parse the first char to make less if statments

	//were the current block sits in the array
	int temp = LocationInArray(curentBlock);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, curentBlock->GetName());

	//Amount of Bombs
	int counter = 0;

	if (location == "TR") {
		if (BoxGrid[temp - Size]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - (Size + 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - 1]->bIsBomb == true) {
			counter++;
		}
	}
	if (location == "MR") {
		if (BoxGrid[temp - Size]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - (Size - 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + (Size - 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + Size]->bIsBomb == true) {
			counter++;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Middle Right")));
	}
	if (location == "BR") {
		if (BoxGrid[temp - 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + (Size - 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + Size]->bIsBomb == true) {
			counter++;
		}
	}
	if (location == "TM") {
		if (BoxGrid[temp + 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - (Size - 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - Size]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - (Size + 1)]->bIsBomb == true) {
			counter++;
		}
	}
	if (location == "MM") {
		if (BoxGrid[temp - (Size + 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - Size]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - (Size - 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + (Size - 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + Size]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + (Size + 1)]->bIsBomb == true) {
			counter++;
		}
	}
	if (location == "BM") {
		if (BoxGrid[temp - 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + (Size - 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + Size]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + (Size + 1)]->bIsBomb == true) {
			counter++;
		}
	}
	if (location == "TL") {
		if (BoxGrid[temp - Size]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - (Size - 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + 1]->bIsBomb == true) {
			counter++;
		}
	}
	if (location == "ML") {
		if (BoxGrid[temp - (Size)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp - (Size - 1)]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + Size]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + (Size + 1)]->bIsBomb == true) {
			counter++;
		}
	}
	if (location == "BL") {
		if (BoxGrid[temp + 1]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + Size]->bIsBomb == true) {
			counter++;
		}
		if (BoxGrid[temp + (Size + 1)]->bIsBomb == true) {
			counter++;
		}
	}

	return counter;
}

void AMyProjectBlockGrid::ZeroClearer(AMyProjectBlock* curentBlock)
{
	int temp = LocationInArray(curentBlock);
	//this is the location of the block on the grid
	FString location = GetLocation(temp);

	if (location == "TR") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size])  == 0) {//if the count comes back 0 then loop again 
			BoxGrid[temp - Size]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1] ) == 0) {
			BoxGrid[temp - 1]->HandleClicked();
		}
	}
	if (location == "MR") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size]) == 0) {
			BoxGrid[temp - Size]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) == 0) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size] ) == 0) {
			BoxGrid[temp + Size]->HandleClicked();
		}
	}
	if (location == "BR") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) == 0) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) == 0) {
			BoxGrid[temp + Size]->HandleClicked();
		}

	}
	if (location == "TM") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) == 0) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) == 0) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size]) == 0) {
			BoxGrid[temp - Size]->HandleClicked();
		}

	}
	if (location == "MM") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size]) == 0) {
			BoxGrid[temp - Size]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) == 0) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) == 0) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) == 0) {
			BoxGrid[temp + Size]->HandleClicked();
		}
	}
	if (location == "BM") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) == 0) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) == 0) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) == 0) {
			BoxGrid[temp + Size]->HandleClicked();
		}

	}
	if (location == "TL") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size]) == 0) {
			BoxGrid[temp - Size]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) == 0) {
			BoxGrid[temp + 1]->HandleClicked();
		}

	}
	if (location == "ML") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - (Size)])), BoxGrid[temp - (Size)]) == 0) {
			BoxGrid[temp - (Size)]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) == 0) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) == 0) {
			BoxGrid[temp + Size]->HandleClicked();
		}
	}
	if (location == "BL") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) == 0) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) == 0) {
			BoxGrid[temp + Size]->HandleClicked();
		}

	}


	if (location == "TR") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size]) ) { 
			BoxGrid[temp - Size]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) ) {
			BoxGrid[temp - 1]->HandleClicked();
		}
	}
	if (location == "MR") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size]) ) {
			BoxGrid[temp - Size]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) ) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) ) {
			BoxGrid[temp + Size]->HandleClicked();
		}
	}
	if (location == "BR") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) ) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) ) {
			BoxGrid[temp + Size]->HandleClicked();
		}

	}
	if (location == "TM") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) ) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) ) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size]) ) {
			BoxGrid[temp - Size]->HandleClicked();
		}

	}
	if (location == "MM") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size]) ) {
			BoxGrid[temp - Size]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1])) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) ) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) ) {
			BoxGrid[temp + Size]->HandleClicked();
		}
	}
	if (location == "BM") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - 1])), BoxGrid[temp - 1]) ) {
			BoxGrid[temp - 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) ) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) ) {
			BoxGrid[temp + Size]->HandleClicked();
		}

	}
	if (location == "TL") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - Size])), BoxGrid[temp - Size]) ) {
			BoxGrid[temp - Size]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) ) {
			BoxGrid[temp + 1]->HandleClicked();
		}

	}
	if (location == "ML") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp - (Size)])), BoxGrid[temp - (Size)])) {
			BoxGrid[temp - (Size)]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) ) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size]) ) {
			BoxGrid[temp + Size]->HandleClicked();
		}
	}
	if (location == "BL") {
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + 1])), BoxGrid[temp + 1]) ) {
			BoxGrid[temp + 1]->HandleClicked();
		}
		if (BombCounter(GetLocation(LocationInArray(BoxGrid[temp + Size])), BoxGrid[temp + Size])) {
			BoxGrid[temp + Size]->HandleClicked();
		}

	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, (location));
}

FString AMyProjectBlockGrid::GetLocation(int temp)
{
	//left
	if (temp % Size == 0){
		//top
		if (BoxGrid.Num() - Size == temp) {
			return "TL";
		}
		//middle
		if (!(0 == temp || BoxGrid.Num() - Size == temp)) {
			return "ML";
		}
		//bottem
		if (0 == temp) {
			return "BL";
		}
	}
	//Right
	if (temp % Size == (Size - 1)){
		//top
		if (temp == (BoxGrid.Num() - 1)){
			return "TR";
		}
		//middle
		if (!(temp == (BoxGrid.Num() - 1) || temp == (Size - 1))){
			return "MR";
		}
		//bottem
		if (temp == (Size - 1)) {
			return "BR";
		}
	}
	//Middle
	if (!(temp % Size == (Size - 1) || temp % Size == 0)){
		//top
		if ((temp < (BoxGrid.Num() - 1)) && (temp >= (BoxGrid.Num() - (Size - 1)))) {
			return "TM";
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, ("TM"));
		}
		//middle
		if ((temp < (BoxGrid.Num() - (Size)) && (temp >= (Size + 1)))) {
			return "MM";
		}
		//bottem 
		if ((temp <= (Size - 2)) && (temp >= 1)) {
			return "BM";
		}
	}
	return "NA";
}

int AMyProjectBlockGrid::LocationInArray(AMyProjectBlock* curentBlock)
{
	//where the current block sits in the array
	int temp = 0;
	//this get the location of the current block in the array
	for (int32 i = 0; i < BoxGrid.Num(); i++) {
		if (BoxGrid[i] == curentBlock) {

			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, curentBlock->GetName());
			temp = i;
		}
	}
	return temp;
}


void AMyProjectBlockGrid::GameOver()
{
	for (int32 BlockIndex = 0; BlockIndex < (Size*Size); BlockIndex++) {
		if (BoxGrid[BlockIndex]->bIsBomb==true) {
			BoxGrid[BlockIndex]->SetToRed();
		}
	}
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Game Over your Score was: {0}"), FText::AsNumber(Score)));
}

void AMyProjectBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
