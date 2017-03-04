// Daniel Alejandro Castro García <dandev237@gmail.com>

#pragma once

#include "GameFramework/Actor.h"
#include "RuntimeMeshActor.generated.h"

UCLASS()
class INFINITECAVERNS_API ARuntimeMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARuntimeMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
