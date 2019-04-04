#include <iostream>
#include <fstream> 
#include <conio.h>
#include <time.h>
#include "Heightmap\Heightmap.h"
#include "Algorithms\Perlin Noise\PerlinNoise.h"
#include "Algorithms\MidPointDisplacement\MidPointDisplacement.h"
#include "Algorithms\Voronoi\VoronoiDiagram.h"
#include "Algorithms\Eroders\Thermal\ThermalEroder.h"
#include "Algorithms\CutAlgorithm\CutAlgorithm.h"
#include <Tools\TerrainGenerationTools.h>

using namespace std;

void PrintHeightMap(const Heightmap& h) {

	if (h.GetWidth() > 16 || h.GetHeight() > 16)
		std::cout << "El Heightmap es demasiado grande" << std::endl;
	else {

		std::cout << "Imprimiendo heightmap" << std::endl;

		for (int i = 0; i < h.GetWidth(); i++) {
			for (int j = 0; j < h.GetHeight(); j++) {
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

	Heightmap h_mpd(exponent);

	MidPointDisplacement mid_point;

	mid_point.GenerateHeightmap(h_mpd);

	h_mpd.DumpToFile("MidPoint");
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

	/*------------------------------------------------------------------------------------------*/
	
	Heightmap h_voronoi(exponent);
	VoronoiDiagram::VoronoiProperties voronoi_p(10, 0.8f, 0.2f);
	VoronoiDiagram voronoi(voronoi_p);

	voronoi.GenerateHeightmap(h_voronoi);
	h_voronoi.DumpToFile("Voronoi");
	std::cout << "Voronoi genereado" << std::endl;
	

	
	/*-----------------------------------------------------------------------------------------*/
	
	

	
	Heightmap h_mixed = tools::MixHeightmaps(h_mpd, h_voronoi, 0.5f, 0.1f);

	//PrintHeightMap(h_mpd);
	h_mixed.DumpToFile("MixedHeightmapPerturbated");

	std::cout << "Heigthmaps mezclados" << std::endl;

	//_getch();
	
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