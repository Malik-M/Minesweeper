// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectPlayerController.h"
#include "MyProjectPawn.h"

AMyProjectGameMode::AMyProjectGameMode()
{
	// no pawn by default
	DefaultPawnClass = AMyProjectPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AMyProjectPlayerController::StaticClass();
}
