#ifndef USERAPI_H
#define USERAPI_H

#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif


#include <string>
#include <Heightmap\Heightmap.h>
#include "Algorithms\Algorithms.h"


using namespace std;



namespace user_api {

	

	static const int MAX_SIZE = 1024;
	static const int MAX_EXPONENT = 10;
	extern "C"{

		TERRAINGENERATOR_API enum class TerrainPreset { Hilly, Soft };
		TERRAINGENERATOR_API enum class BaseAlgorithm { PerlinNoise, DiamondSquare };
		TERRAINGENERATOR_API enum class ErosionLevel { None, Low, Mid, High };
	
	}
	

	extern "C" TERRAINGENERATOR_API struct TerrainProperties {

		TerrainProperties() = default;
		TERRAINGENERATOR_API TerrainProperties(TerrainPreset preset);
		TerrainProperties(BaseAlgorithm, int,float, float, float, float,ErosionLevel, bool);
		//TerrainPrperties(Initia)

		//Algoritmo utilizado para la base
		BaseAlgorithm base_algorithm;
		//Numero de montañas totales que habrá en el terreno.
		int number_of_mountains;
		//Factor de aleatoreidad que indica cómo de randomizado será el terreno.
		float random_factor;
		//Factor de accientado: determina cómo de accidentado será el terreno
		float hilly_factor;
		//Factor de suavidad: a pesar de ser accidentado, el terreno puede estar más o menos suavizado
		float smooth_factor;
		//Factor de rios: controla la creación de "caudales" para los rios
		float river_factor;
		//Nivel de erosion
		ErosionLevel erosion_level;
		//Si el terreno es una isla, los puntos de su alrededor valdrán cero
		bool is_island;
	private:
		void SetDefaultProperties(const TerrainProperties);
	};


	extern "C" TERRAINGENERATOR_API class Terrain {
	private:
		Heightmap heightmap;

	public:
	
		explicit Terrain(Heightmap&& h);

		TERRAINGENERATOR_API void CreateRaw(string path);
		
	};


	extern "C" TERRAINGENERATOR_API Terrain GenerateTerrain(int size, const TerrainProperties& terrain_properties);

	Heightmap CreateBase(int size, const TerrainProperties& p);
	Heightmap CreateMountains(int size, const TerrainProperties& p);
	void CutHeightmap(Heightmap& h, const TerrainProperties p);

	MidPointDisplacement::Properties GetDiamondSquareProp(const TerrainProperties& p);
	VoronoiDiagram::Properties GetVoronoiProp(const TerrainProperties& p);
	pair<int,int> GetMixValues(const TerrainProperties& t);

}
#endif