
#include <string>
#include <Heightmap\Heightmap.h>

using namespace std;

namespace user_api {

	static const int MAX_SIZE = 1024;
	static const int MAX_EXPONENT = 10;

	struct TerrainProperties {
		enum class Preset { None, Hilly, Soft };

		TerrainProperties();

		//Numero de monta�as totales que habr� en el terreno.
		int number_of_mountains;
		//Factor de accientado: determina c�mo de accidentado ser� el terreno
		float hilly_factor;
		//Factor de suavidad: a pesar de ser accidentado, el terreno puede estar m�s o menos suavizado
		float smooth_factor;
		//Factor de rios: controla la creaci�n de "caudales" para los rios
		float river_factor;
		//Si el terreno es una isla, los puntos de su alrededor valdr�n cero
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