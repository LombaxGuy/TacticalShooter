// Fill out your copyright notice in the Description page of Project Settings.

#include "TacticalShooter.h"
#include "AttackComponent.h"


// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAttackComponent::CalculateDamage()
{
	AActor * Player = GetOwner();
	FRotator playerRotation = Player->GetActorRotation();
	FVector RayEnd = myLocation + playerRotation.Vector() * pawnDistance;
	FHitResult HitResult;
	bool DidHitSomeThing = GetWorld()->LineTraceSingleByObjectType(HitResult, myLocation, RayEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic), FCollisionQueryParams(FName(TEXT("ActionTrace")), false, GetOwner()));
	if (DidHitSomeThing)
	{
		hitChance += 1;
	}
	else
	{
		hitChance -= 1;
	}

	if (hitChance == 1)
	{
		int rng = FMath::RandRange(1, 2);
		if (rng == 1)
		{
			damageTaken = 4;
		}
	}
	else if (hitChance == 2)
	{
		int rng = FMath::RandRange(1, 4);
		if (rng == 1)
		{
			damageTaken = 3;
		}
	}
	else
	{
		damageTaken = 2;
	}

	if (hitChance > 1)
	{
		isHit = FMath::RandRange(1, hitChance);
	}
	else
	{
		isHit = 1;
	}

}

void UAttackComponent::CalculateDistance(AActor* target)
{
	AActor * Player = GetOwner();
	targetLocation = target->GetActorLocation();
	myLocation = Player->GetActorLocation();

	FVector vectorBetweenPawns = myLocation - targetLocation;

	pawnDistance = vectorBetweenPawns.Size();

	if (pawnDistance <= attackRange)
	{
		inRange = true;
	}
	else
	{
		inRange = false;
	}

	if (inRange == true)
	{
		if (pawnDistance <= (attackRange / 5))
		{
			hitChance = 2;
		}
		else if (pawnDistance <= (attackRange / 3))
		{
			hitChance = 3;
		}
		else if (pawnDistance <= (attackRange / 2))
		{
			hitChance = 4;
		}
		else
		{
			hitChance = 5;
		}
	}

}

AActor* UAttackComponent::Attack(AActor* target)
{
	AActor * player = GetOwner();
	if (player->Tags.Contains("Team1") && target->Tags.Contains("Team2"))
	{
		CalculateDistance(target);
		if (inRange == true)
		{
			CalculateDamage();
		}

		return target;
	}
	else if (player->Tags.Contains("Team2") && target->Tags.Contains("Team1"))
	{
		CalculateDistance(target);
		if (inRange == true)
		{
			CalculateDamage();
		}
		return target;
	}
	else
	{
		return nullptr;
	}

}



// Called every frame
void UAttackComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

