#include <iostream>
#include <fstream> 
#include <conio.h>
#include <time.h>
#include <chrono>
#include "Heightmap\Heightmap.h"
#include "Algorithms\Algorithms.h"
#include "Algorithms\Eroders\Eroders.h"
#include <Tools\TerrainGenerationTools.h>
#include "UserAPI\UserAPI.h"

using namespace std;
using namespace chrono;

void PrintHeightMap(const Heightmap& h) {

	if (h.GetSize() > 16)
		std::cout << "El Heightmap es demasiado grande" << std::endl;
	else {

		std::cout << "Imprimiendo heightmap" << std::endl;

		for (int i = 0; i < h.GetSize(); i++) {
			for (int j = 0; j < h.GetSize(); j++) {
				//std::cout << FloatToShortInt(_heightMap[i][j]) << " - ";
				std::cout << h[i][j] << " - ";

			}
			std::cout << std::endl;
		}
	}

}


int main() {

	constexpr int exponent = 10;
	int randSeed = static_cast<int>(duration_cast<minutes>(
		system_clock::now().time_since_epoch()).count());
	srand(randSeed); //TODO: meter inicialización a la libreria para esto

	//Heightmap h(exponent);

	//DiamondSquare mid_point;

	//mid_point.GenerateHeightmap(h_mpd);

	//h_mpd.DumpToFile("MidPoint");
	/*
	DiamondSquare mpd({ 0.3f, 0.5f });

	mpd.GenerateHeightmap(h_mpd);

	h_mpd.DumpToFile("CutAlgorithm/MidPoint");

	std::cout << "Mid point generado" << std::endl;
	//_getch();

	
	CutAlgorithm cutAlgorithm{};

	cutAlgorithm.CutHeightmap(h_mpd);

	h_mpd.DumpToFile("CutAlgorithm/MidPointCutted");
	*/
	/*------------------------------------------------------- PERLIN NOISE --------------------------------------------*/

	/*Heightmap perlin_heightmap(exponent);
	PerlinNoise::Properties p_p;
	PerlinNoise perlin_algorithm(p_p);

	perlin_algorithm.GenerateHeightmap(perlin_heightmap);

	perlin_heightmap.DumpToFile("PerlinNoise/Heightmap");




	/*------------------------------------------------------- PERLIN NOISE --------------------------------------------*/
	/*---------------------------- VORONOI ---------------------------------------
	
	VoronoiDiagram::Properties voronoi_p1(10, 1.0f, 0.8f);
	VoronoiDiagram::Properties voronoi_p2(10, 0.5f, 0.5f);
	VoronoiDiagram::Properties voronoi_p3(10, 0.2f, 0.0f, 0.1f);

	Heightmap heightmap_1(exponent);
	Heightmap heightmap_2(exponent);
	Heightmap heightmap_3(exponent);

	VoronoiDiagram voronoi(voronoi_p1);
	voronoi.GenerateHeightmap(heightmap_1);
	heightmap_1.DumpToFile("Voronoi/Voronoi1");

	voronoi = { voronoi_p2 };
	voronoi.GenerateHeightmap(heightmap_2);
	heightmap_2.DumpToFile("Voronoi/Voronoi2");

	voronoi = { voronoi_p3 };
	voronoi.GenerateHeightmap(heightmap_3);
	heightmap_3.DumpToFile("Voronoi/Voronoi3");


	std::cout << "Voronoi generado" << std::endl;
	

	
	/*------------------------------------ VORONOI -----------------------------------------*/
	
	/*------------------------------------ DIAMOND-SQUARE ----------------------------------*/
	
	/*DiamondSquare::Properties ds_p1(0.5f, 0.5f);
	DiamondSquare::Properties ds_p2(0.1f, 0.5f);
	DiamondSquare::Properties ds_p3(0.8f, 0.3f);
	

	Heightmap heightmap_1(exponent);
	Heightmap heightmap_2(exponent);
	Heightmap heightmap_3(exponent);

	DiamondSquare diamond_square(ds_p1);
	diamond_square.GenerateHeightmap(heightmap_1);
	//heightmap_1.DumpToFile("DiamondSquare/DiamondSquare1");

	diamond_square = { ds_p2 };
	diamond_square.GenerateHeightmap(heightmap_2);
	//heightmap_2.DumpToFile("DiamondSquare/DiamondSquare2");

	diamond_square = { ds_p3 };
	diamond_square.GenerateHeightmap(heightmap_3);
	heightmap_3.DumpToFile("DiamondSquare/DiamondSquare4");




	std::cout << "Diamond-Square generados" << std::endl;
	/*------------------------------------ DIAMOND-SQUARE ----------------------------------*/

	/*------------------------------------ CUT ALGORITHM AND MIXED HEIGHTMAPS  ----------------------------------*/

	/*DiamondSquare::Properties ds_p1(0.5f, 0.5f);
	VoronoiDiagram::Properties vd_p(5);
	CutAlgorithm::Properties ca_p(5, 0.5f);

	Heightmap heightmap_ds(exponent);
	Heightmap heightmap_voronoi(exponent);

	DiamondSquare diamond_square(ds_p1);
	diamond_square.GenerateHeightmap(heightmap_ds);
	heightmap_ds.DumpToFile("DiamondSquare");

	VoronoiDiagram voronoi_algorithm(vd_p);
	voronoi_algorithm.GenerateHeightmap(heightmap_voronoi);
	heightmap_voronoi.DumpToFile("Voronoi");

	CutAlgorithm cut_algorithm(ca_p);

	cut_algorithm.CutHeightmap(heightmap_ds);
	heightmap_ds.DumpToFile("CutDiamondSquare");
	cut_algorithm.CutHeightmap(heightmap_voronoi);
	heightmap_voronoi.DumpToFile("CutVoronoi");

	Heightmap h_mixed = tools::MixHeightmaps(heightmap_ds, heightmap_voronoi, 0.5f, 0.1f);
	h_mixed.DumpToFile("Mixed");


	/*------------------------------------ CUT ALGORITHM  ----------------------------------*/

	/*
	Heightmap h_mixed = tools::MixHeightmaps(h_mpd, h_voronoi, 0.5f, 0.1f);

	//PrintHeightMap(h_mpd);
	h_mixed.DumpToFile("MixedHeightmapPerturbated");

	std::cout << "Heigthmaps mezclados" << std::endl;

	//_getch();
	
	*/

	/*------------------------------------------------------------------------------------------*/

	/*
	ErosionProperties erosion_hydraulic(ErosionType::HYDRAULIC);
	ErosionProperties erosion_thermal(ErosionType::THERMAL);
	
	Heightmap h_thermal(h_mixed);
	Heightmap h_hydraulic(h_mixed);


	ErodeHeightmap(h_thermal, erosion_thermal);
	ErodeHeightmap(h_hydraulic, erosion_hydraulic);

	h_thermal.DumpToFile("ErodedThermal");
	h_hydraulic.DumpToFile("ErodedHydraylic");
	*/

/*---------------------------------------------------------------- USER API -----------------------------------------------*/



	user_api::Terrain terrain = user_api::GenerateTerrain(8, user_api::TerrainPreset::Soft);

	terrain.CreateRaw("Terrain");

/*---------------------------------------------------------------- USER API -----------------------------------------------*/
	return 0;
}