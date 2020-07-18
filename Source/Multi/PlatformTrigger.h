// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformCube.h"

#include "PlatformTrigger.generated.h"

//** When player steps onto the trigger, it adds to the number of active triggers. Each trigger platform has corresponding platformcubes that
//** will be activated by that trigger (set in bp). If total number of active triggers are met, the cubes start moving.

UCLASS()
class MULTI_API APlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformTrigger();


protected:
	/** Components **/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Setup")
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Setup")
		class UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Setup")
		class UStaticMeshComponent* StaticMesh;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/** FUNCTIONS **/
	// Called every frame
	virtual void Tick(float DeltaTime) override;

/** PRIVATE PROPERTIES **/
private:
	UPROPERTY(EditAnywhere)
	TArray<APlatformCube*> PlatformsToTrigger; 

private:

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
