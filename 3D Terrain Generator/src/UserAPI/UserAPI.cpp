#include "UserAPI.h"


user_api::Terrain::Terrain(int w, int h, TerrainProperties)
{
	int width = (w < 0 || w > MAX_SIZE) ? 256 : w;
	int height = (h < 0 || h > MAX_SIZE) ? 256 : h;

	heightmap = Heightmap(width,height);
}

user_api::Terrain::Terrain(int e, TerrainProperties)
{
	int exponent = (e < 0 || e > MAX_EXPONENT) ? 8 : e;

	heightmap = Heightmap(exponent);
}

int user_api::GenerateTerrain(const Terrain & t, const TerrainProperties p)
{
	return 0;
}

user_api::TerrainProperties::TerrainProperties()
{
}
