
#include <string>
#include <Heightmap\Heightmap.h>

using namespace std;

namespace user_api {

	static const int MAX_SIZE = 1024;
	static const int MAX_EXPONENT = 10;

	struct TerrainProperties {
		enum class Preset { None, Hilly, Soft };

		TerrainProperties();

		//Numero de montañas totales que habrá en el terreno.
		int number_of_mountains;
		//Factor de accientado: determina cómo de accidentado será el terreno
		float hilly_factor;
		//Factor de suavidad: a pesar de ser accidentado, el terreno puede estar más o menos suavizado
		float smooth_factor;
		//Factor de rios: controla la creación de "caudales" para los rios
		float river_factor;
		//Si el terreno es una isla, los puntos de su alrededor valdrán cero
		bool is_island;
	};



	class Terrain {
	private:
		Heightmap heightmap;
		TerrainProperties properties;

	public:
		Terrain(int width, int height, TerrainProperties = {});
		Terrain(int exponent, TerrainProperties = {});
		
	};


	int GenerateTerrain(const Terrain &t, const TerrainProperties terrain_properties);


}