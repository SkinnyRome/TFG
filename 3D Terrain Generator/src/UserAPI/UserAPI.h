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

	TERRAINGENERATOR_API enum class TerrainPreset {Hilly, Soft };
	TERRAINGENERATOR_API enum class BaseAlgorithm {PerlinNoise, DiamondSquare};

	TERRAINGENERATOR_API struct TerrainProperties {

		TerrainProperties() = default;
		explicit TerrainProperties(TerrainPreset preset);
		TerrainProperties(BaseAlgorithm, int,float, float, float, float, bool);
		//TerrainPrperties(Initia)

		//Algoritmo utilizado para la base
		BaseAlgorithm base_algorithm;
		//Numero de monta�as totales que habr� en el terreno.
		int number_of_mountains;
		//Factor de aleatoreidad que indica c�mo de randomizado ser� el terreno.
		float random_factor;
		//Factor de accientado: determina c�mo de accidentado ser� el terreno
		float hilly_factor;
		//Factor de suavidad: a pesar de ser accidentado, el terreno puede estar m�s o menos suavizado
		float smooth_factor;
		//Factor de rios: controla la creaci�n de "caudales" para los rios
		float river_factor;
		//Si el terreno es una isla, los puntos de su alrededor valdr�n cero
		bool is_island;
	private:
		void SetDefaultProperties(const TerrainProperties);
	};
	
	static const TerrainProperties hilly_preset;
	static const TerrainProperties soft_preset;


	TERRAINGENERATOR_API class Terrain {
	private:
		Heightmap heightmap;

	public:
	
		Terrain(int size);
		
	};


	TERRAINGENERATOR_API Terrain GenerateTerrain(int size, const TerrainProperties& terrain_properties);

	Heightmap CreateBase(int size, const TerrainProperties& p);
	Heightmap CreateMountains(int size, const TerrainProperties& p);
	void CutHeightmap(Heightmap& h, const TerrainProperties p);

	MidPointDisplacement::Properties GetDiamondSquareProp(const TerrainProperties& p);
	VoronoiDiagram::Properties GetVoronoiProp(const TerrainProperties& p);

}
#endif