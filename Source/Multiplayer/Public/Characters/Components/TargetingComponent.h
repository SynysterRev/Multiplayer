// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetChangedEvent, AActor*, NewTarget);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYER_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(Transient)
	TObjectPtr<AActor> CurrentTarget = nullptr;
	
	UPROPERTY(Replicated) // Optionnel
	TObjectPtr<AActor> MarkedTarget = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Targeting")
	float MaxDistanceTargeting = 4000.0f;
	
	AActor* FindClosestTarget();
	void TryTargetActor(AActor* Target);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/*Set the target for the local player*/
	void SetTarget(AActor* Target);
	
	/*Mark the target and replicate the target, so allies can target the same actor*/
	void MarkTarget();
	
	UFUNCTION(Server, Reliable)
	void ServerMarkTarget(AActor* NewTarget);
	
	UPROPERTY(BlueprintAssignable)
	FTargetChangedEvent OnTargetChanged;
	
	UPROPERTY(BlueprintAssignable)
	FTargetChangedEvent OnMarkedTargetChanged;
};
