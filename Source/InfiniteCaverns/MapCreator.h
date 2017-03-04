// Daniel Alejandro Castro García <dandev237@gmail.com>

#pragma once

#include "Engine/LevelScriptActor.h"
#include "MapCreator.generated.h"

/**
 * 
 */
UCLASS()
class INFINITECAVERNS_API AMapCreator : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = CavernGenerator)
	void GenerateCavern(const int32 Width, const int32 Height, const int32 WallPercentage, const int32 SmoothingIterations, const int32 Seed);

private:
	int32 GetSorroundingWallsOfCell(const TArray<int32> &Map, const int32 &CellIndex, const int32 &Width, const int32 &Height);

	bool IsValidIndex(const int32 &Index, const int32 &Width, const int32 &Height);

	bool IsInEdgeOfMap(const int32 &Index, const int32 &Width, const int32 &Height);

};