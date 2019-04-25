#include "UserAPI.h"


using user_api::Terrain;
using user_api::TerrainProperties;
using user_api::BaseAlgorithm;

TerrainProperties hilly_preset = { BaseAlgorithm::PerlinNoise, 15, 0.4f, 0.8f, 0.3f, 0.5f, false};
TerrainProperties soft_preset = { BaseAlgorithm::PerlinNoise, 3, 0.2f, 0.3f, 0.8f, 0.2f, false};


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
	//3. Cut base heightmap if necessary
	if (properties.hilly_factor >= 0.4f) {
		CutHeightmap(base_heightmap, properties);
	}
	//4. Mix Heightmaps

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
		base_algorithm = new MidPointDisplacement(GetDiamondSquareProp(p));
		break;
	default:
		base_algorithm = new PerlinNoise();
		break;
	}

	base_algorithm->GenerateHeightmap(h);

	delete base_algorithm;
	return h;
}

Heightmap user_api::CreateMountains(int size, const TerrainProperties & p)
{
	Heightmap h(size);

	VoronoiDiagram voronoi_algorithm(GetVoronoiProp(p));

	voronoi_algorithm.GenerateHeightmap(h);
	
	return h;
}

void user_api::CutHeightmap(Heightmap & h, const TerrainProperties p)
{
	int num_of_slopes;
	float roughness;

	num_of_slopes = 3 + static_cast<int>(floorf(10.0f * p.hilly_factor));

	roughness = p.hilly_factor * 0.7f;

	CutAlgorithm cut_algorithm({ num_of_slopes,roughness });

	cut_algorithm.CutHeightmap(h);
}

MidPointDisplacement::Properties user_api::GetDiamondSquareProp(const TerrainProperties & p)
{
	float spread, roughness;

	//Calculate spread.
	spread = (1.0f * p.hilly_factor) - (0.3f * p.smooth_factor);
	//Calculate roughness.
	roughness = 1.0f - (0.8f * p.smooth_factor);

	return MidPointDisplacement::Properties(spread, roughness);
}

VoronoiDiagram::Properties user_api::GetVoronoiProp(const TerrainProperties & p)
{

	int num_of_sites;
	float slope_softness, distance_between, average_height;

	//Set num of mountains.
	num_of_sites = p.number_of_mountains;
	//Claculate variables
	average_height = 0.5f + (0.4f * p.hilly_factor) + (num_of_sites >= 10 ? 0.0f : 1.0f);
	distance_between = 0.5f * p.river_factor;
	slope_softness = p.smooth_factor;
	
	return VoronoiDiagram::Properties(num_of_sites,slope_softness, distance_between, average_height);
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

user_api::TerrainProperties::TerrainProperties(BaseAlgorithm alg, int m, float ra, float hf, float sf, float rf, bool isl):
	base_algorithm(alg),
	number_of_mountains(m),
	random_factor(ra),
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
