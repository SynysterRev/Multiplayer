// Copyright Epic Games, Inc. All Rights Reserved.


#include "MultiplayerPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Multiplayer.h"
#include "NavigationSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Characters/MultiplayerCharacter.h"
#include "Characters/Components/TargetingComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Net/UnrealNetwork.h"
#include "UI/RootGameUIPanel.h"
#include "Widgets/Input/SVirtualJoystick.h"

DEFINE_LOG_CATEGORY(LogMultiplayerPlayerController);

AMultiplayerPlayerController::AMultiplayerPlayerController()
{
	PathFollowingComponent = CreateDefaultSubobject<UPathFollowingComponent>(TEXT("PathFollowingComponent"));
}

AMultiplayerCharacter* AMultiplayerPlayerController::GetMultiplayerCharacter() const
{
	return MultiplayerCharacter;
}

void AMultiplayerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	MultiplayerCharacter = Cast<AMultiplayerCharacter>(GetPawn());
	
	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);
		}
		else
		{
			UE_LOG(LogMultiplayer, Error, TEXT("Could not spawn mobile controls widget."));
		}
	}

	bShowMouseCursor = true;
	
	if (IsLocalPlayerController())
	{
		if (RootGameUIPanelClass)
		{
			RootGameUIPanel = Cast<URootGameUIPanel>(CreateWidget(this, RootGameUIPanelClass));
		
			if (!RootGameUIPanel)
			{
				UE_LOG(LogMultiplayerPlayerController, Warning, TEXT("Failed to create RootGameUIPanel"));
				return;
			}
			RootGameUIPanel->AddToViewport();
		}
		else
		{
			UE_LOG(LogMultiplayerPlayerController, Warning, TEXT("No root UI class set in the controller"));
		}
	}
}

void AMultiplayerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
			if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
			{
				EnhancedInput->BindAction(LeftClickAction, ETriggerEvent::Started, this,
				                          &AMultiplayerPlayerController::OnClick);
			}
		}
	}
}

void AMultiplayerPlayerController::OnClick()
{
	FHitResult Hit;

	if (GetHitResultUnderCursor(ECC_Interactable, false, Hit))
	{
		UE_LOG(LogMultiplayer, Log, TEXT("'%s' Actor find"), *Hit.GetActor()->GetName());
		
		if (!MultiplayerCharacter)
		{
			return;
		}
		
		if (UTargetingComponent* TargetingComponent = MultiplayerCharacter->GetTargetingComponent())
		{
			TargetingComponent->SetTarget(Hit.GetActor());
		}
	}
	// if (GetHitResultUnderCursor(ECC_Ground, false, Hit))
	// {
	// 	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Hit.ImpactPoint, FRotator::ZeroRotator,
	// 	                                               FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	// 	// UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.ImpactPoint);
	// 	ServerMoveToLocation(Hit.ImpactPoint);
	// 	
	// }
}

void AMultiplayerPlayerController::MoveToLocation(const FVector& TargetLocation)
{
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys) return;

	FNavLocation NavLoc;
	if (NavSys->ProjectPointToNavigation(TargetLocation, NavLoc, FVector(500, 500, 500)))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NavLoc.Location);
	}
}

void AMultiplayerPlayerController::ServerMoveToLocation_Implementation(const FVector& TargetLocation)
{
	if (!HasAuthority())
		return;

	MoveToLocation(TargetLocation);
}
