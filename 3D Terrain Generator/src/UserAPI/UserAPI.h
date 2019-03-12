
#include <string>
using namespace std;

namespace user_api {




	struct TerrainProperties {
		enum class Preset { None, Hilly, Soft };

		float mountain_factor = 0.5f;
		float smooth_factor = 0.5f;
		float river_factor = 0.2f;
		bool is_island = false;
	};

	struct Terrain {
		int width = 0;
		int height = 0;
		int exponent = 0;
		TerrainProperties properties;

		Terrain(int witdh = 0, int height = 0, TerrainProperties = TerrainProperties());
		Terrain(int exponent, TerrainProperties = TerrainProperties());
		

	};


	int CreateTerrain(const Terrain &t, const string fileName /*flags*/);


}