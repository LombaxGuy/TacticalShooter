// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICALSHOOTER_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UInputComponent *InputComponent = nullptr;
	UPhysicsHandleComponent *PhysicsComponent = nullptr;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariable)
		bool inRange = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariable)
		float rayReach = 100.0f;

	float attackRange = 1500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariable)
		int damageTaken = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariable)
		int hitChance = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariable)
		int isHit;

	float pawnDistance;

	FVector myLocation;
	FVector targetLocation;

	// Sets default values for this component's properties
	UAttackComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = AttackFunction)
		AActor* Attack(AActor* target);

	void CalculateDamage();

	UFUNCTION(BlueprintCallable, Category = AttackFunction)
		bool CalculateDistance(AActor* target);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



	
};
