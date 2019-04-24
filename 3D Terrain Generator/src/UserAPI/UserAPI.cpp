#include "UserAPI.h"
#include "Algorithms\Algorithms.h"


using user_api::Terrain;
using user_api::TerrainProperties;
using user_api::BaseAlgorithm;

TerrainProperties hilly_preset = { BaseAlgorithm::PerlinNoise, 15, 0.8f, 0.3f, 0.5f, false};
TerrainProperties soft_preset = { BaseAlgorithm::PerlinNoise, 3, 0.3f, 0.8f, 0.2f, false};


Terrain::Terrain(int size)
{

	heightmap = Heightmap(size);
}


Terrain user_api::GenerateTerrain(int size, const TerrainProperties& properties)
{

	//1. Create Base Terrain
	Heightmap base_heightmap = CreateBase(size, properties);
	//2. Generate Mountains Heightmap
	Heightmap mountains_heightmap = CreateMountains(size, properties);
	//3. Mix Heightmaps

	return 0;
}

Heightmap user_api::CreateBase(int size, const TerrainProperties & p)
{
	IAlgorithm* base_algorithm;
	Heightmap h(size);

	switch (p.base_algorithm) {
	case BaseAlgorithm::PerlinNoise:
		base_algorithm = new PerlinNoise();
		break;
	case BaseAlgorithm::DiamondSquare:
		base_algorithm = new MidPointDisplacement();
		break;
	default:
		break;
	}
	delete base_algorithm;
	return h;
}

Heightmap user_api::CreateMountains(int size, const TerrainProperties & p)
{
	Heightmap h(size);

	

	return h;
}

user_api::TerrainProperties::TerrainProperties(TerrainPreset preset)
{
	switch (preset)
	{
	case user_api::TerrainPreset::Hilly:
		SetDefaultProperties(hilly_preset);
		break;
	case user_api::TerrainPreset::Soft:
		SetDefaultProperties(soft_preset);
		break;
	default:
		break;
	}
}

user_api::TerrainProperties::TerrainProperties(BaseAlgorithm alg, int m, float hf, float sf, float rf, bool isl):
	base_algorithm(alg),
	number_of_mountains(m),
	hilly_factor(hf),
	smooth_factor(sf),
	river_factor(rf),
	is_island(isl)
{
}

void user_api::TerrainProperties::SetDefaultProperties(const TerrainProperties t)
{
	base_algorithm = t.base_algorithm;
	number_of_mountains = t.number_of_mountains;
	hilly_factor = t.hilly_factor;
	smooth_factor = t.smooth_factor;
	river_factor = t.river_factor;
	is_island = t.is_island;
}
