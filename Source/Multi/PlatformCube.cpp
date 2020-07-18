// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformCube.h"

#include "Components/SceneComponent.h"
#include "Math/Vector.h"

//** When player steps onto the trigger, it adds to the number of active triggers. Each trigger platform has corresponding platformcubes that
//** will be activated by that trigger (set in bp). If total number of active triggers are met, the cubes start moving.

// Sets default values
APlatformCube::APlatformCube() : Speed(2.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = Root;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Root);
	StaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	StaticMesh->SetMobility(EComponentMobility::Movable);

}

// Called when the game starts or when spawned
void APlatformCube::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		/** Set start location of actor to use in movement**/
		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	}
	
}

// Called every frame
void APlatformCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(HasAuthority())
	{	
		if(ActiveTriggers >= 1)
		{
			MovePlatform(DeltaTime);
		}
	}
}

void APlatformCube::MovePlatform(float DeltaTimeIn)
{
	FVector Location = GetActorLocation();
	float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
	float JourneyTravelled = (Location - GlobalStartLocation).Size();

	if(JourneyTravelled >= JourneyLength)
	{
		FVector Swap = GlobalStartLocation;
		GlobalStartLocation = GlobalTargetLocation;
		GlobalTargetLocation = Swap;
	}

	FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
	Location += Speed * DeltaTimeIn * Direction;
	SetActorLocation(Location);

}

void APlatformCube::AddActiveTrigger()
{
	ActiveTriggers = ActiveTriggers + 1;
}

void APlatformCube::RemoveActiveTrigger()
{
	if(ActiveTriggers > 0)
	{
		ActiveTriggers = ActiveTriggers - 1;

	}
}

