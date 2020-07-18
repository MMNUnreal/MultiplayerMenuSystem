// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformCube.generated.h"

//** When player steps onto the trigger, it adds to the number of active triggers. Each trigger platform has corresponding platformcubes that
//** will be activated by that trigger (set in bp). If total number of active triggers are met, the cubes start moving.

UCLASS()
class MULTI_API APlatformCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformCube();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
	class UStaticMeshComponent* StaticMesh;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//** Controls movement of platform **//
	void MovePlatform(float DeltaTimeIn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	/** PUBLIC FUNCTIONS **/
public:
	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:

	FVector GlobalStartLocation;
	FVector NewTargetLocation;
	FVector GlobalTargetLocation;

	/** Properties **/
	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 0;


};
