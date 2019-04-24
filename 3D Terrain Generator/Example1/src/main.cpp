#include <iostream>
#include <fstream> 
#include <conio.h>
#include <time.h>
#include "Heightmap\Heightmap.h"
#include "Algorithms\Algorithms.h"
#include "Algorithms\Eroders\Eroders.h"
#include <Tools\TerrainGenerationTools.h>

using namespace std;

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

	constexpr int exponent = 8;

	srand(time(NULL)); //TODO: meter inicialización a la libreria para esto

	//Heightmap h(exponent);

	//MidPointDisplacement mid_point;

	//mid_point.GenerateHeightmap(h_mpd);

	//h_mpd.DumpToFile("MidPoint");
	/*
	MidPointDisplacement mpd({ 0.3f, 0.5f });

	mpd.GenerateHeightmap(h_mpd);

	h_mpd.DumpToFile("CutAlgorithm/MidPoint");

	std::cout << "Mid point generado" << std::endl;
	//_getch();

	
	CutAlgorithm cutAlgorithm{};

	cutAlgorithm.CutHeightmap(h_mpd);

	h_mpd.DumpToFile("CutAlgorithm/MidPointCutted");
	*/

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
	
	MidPointDisplacement::Properties ds_p1(0.5f, 0.5f);
	MidPointDisplacement::Properties ds_p2(0.1f, 0.5f);
	MidPointDisplacement::Properties ds_p3(0.8f, 0.3f);
	

	Heightmap heightmap_1(exponent);
	Heightmap heightmap_2(exponent);
	Heightmap heightmap_3(exponent);

	MidPointDisplacement diamond_square(ds_p1);
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
	return 0;
}