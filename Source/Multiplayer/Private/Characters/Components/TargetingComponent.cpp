// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/TargetingComponent.h"

#include "Interfaces/Interactable.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


AActor* UTargetingComponent::FindClosestTarget()
{
	
	return nullptr;
}

// Called every frame
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTargetingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTargetingComponent, MarkedTarget);
}

void UTargetingComponent::TryTargetActor(AActor* Target)
{
	if (!Target) return;
	
	if (Target->Implements<UInteractable>())
	{
		SetTarget(Target);
	}
}

void UTargetingComponent::SetTarget(AActor* Target)
{
	if (CurrentTarget == Target) return;
	CurrentTarget = Target;
	OnTargetChanged.Broadcast(CurrentTarget);
}

void UTargetingComponent::MarkTarget()
{
	if (!CurrentTarget) return;
	
	if (!GetOwner()->HasAuthority())
	{
		ServerMarkTarget(CurrentTarget);
		return;
	}
	MarkedTarget = CurrentTarget;
	OnMarkedTargetChanged.Broadcast(MarkedTarget);
}

void UTargetingComponent::ServerMarkTarget_Implementation(AActor* NewTarget)
{
	MarkedTarget = NewTarget;
	OnMarkedTargetChanged.Broadcast(MarkedTarget);
}

