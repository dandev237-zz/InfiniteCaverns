// Daniel Alejandro Castro García <dandev237@gmail.com>

#include "InfiniteCaverns.h"
#include "MapCreator.h"
#include "MeshCreator.h"

void AMapCreator::GenerateCavern(const int32 Width, const int32 Height, const int32 WallPercentage, const int32 SmoothingIterations)
{
	TArray<int32> Map;
	Map.Reserve(Width*Height);

	//Randomly fill map with 0's and 1's
	//0 -> Floor (Passable terrain)
	//1 -> Wall (Impassable terrain)
	for (int i = 0; i < Width * Height; ++i)
	{
		if (IsInEdgeOfMap(i, Width, Height))		//Cell is at the edge of the map
		{
			Map.Add(1);								//Make it a wall
		}
		else
		{
			int RandomNumber = rand() % 100 + 1;	//Generate random number between 0 and 100
			Map.Add(RandomNumber < WallPercentage ? 1 : 0);
		}
	}

	int32 SmoothingCounter = 0;
	while (SmoothingCounter < SmoothingIterations)
	{
		//Cellular automaton smoothing iterations
		for (int i = 0; i < (Width * Height); ++i)
		{
			if (!IsInEdgeOfMap(i, Width, Height))
			{
				int SorroundingWallsOfCell = GetSorroundingWallsOfCell(Map, i, Width, Height);

				if (SorroundingWallsOfCell > 4)
				{
					Map[i] = 1;	//Transform cell to wall
				}
				else if (SorroundingWallsOfCell < 4)
				{
					Map[i] = 0;	//Transform cell to floor
				}
			}
		}
		++SmoothingCounter;
	}

	//Create the mesh
	MeshCreator MeshGen = MeshCreator();
	MeshGen.CreateDynamicMesh(Map, 1.0f, Width, Height);

	for (int i = 0; i < Width; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			if (Map[j*Width + i] == 1)
			{
				DrawDebugBox(GetWorld(), FVector(100 * i, 100 * j, 0), FVector(45, 45, 45), FColor::Black, false, 5.0f);
			}
		}
	}
}

int32 AMapCreator::GetSorroundingWallsOfCell(const TArray<int32> &Map, const int32 &CellIndex, const int32 &Width, const int32 &Height)
{
	int32 SorroundingWalls = 0;

	//Moor Neighborhood: 8 adjacents
	TArray<int32> Indexes;
	Indexes.Reserve(8);
	Indexes.Add(CellIndex - (Width - 1));	//Upper left
	Indexes.Add(CellIndex - Width);			//Upper
	Indexes.Add(CellIndex - (Width + 1));	//Upper right
	Indexes.Add(CellIndex - 1);				//Left
	Indexes.Add(CellIndex + 1);				//Right
	Indexes.Add(CellIndex + (Width - 1));	//Lower left
	Indexes.Add(CellIndex + Width);			//Lower
	Indexes.Add(CellIndex + (Width + 1));;	//Lower right

	for (int32 Index : Indexes)
	{
		if (IsValidIndex(Index, Width, Height))
		{
			SorroundingWalls += Map[Index];
		}
	}

	return SorroundingWalls;
}

bool AMapCreator::IsValidIndex(const int32 &Index, const int32 &Width, const int32 &Height)
{
	return (Index >= 0 && Index % Width != 0 && Index < (Width * Height));
}

bool AMapCreator::IsInEdgeOfMap(const int32 &Index, const int32 &Width, const int32 &Height)
{
	//Upper edge, Lower edge, Left edge, Right edge
	return (Index / Width == 0 || (Index >= (Width * (Height - 1)) && Index <= (Width * Height) - 1) || Index % Width == 0 || Index % Width == Width - 1);
}