#include <iostream>
#include <fstream> 
#include <conio.h>
#include <time.h>
#include "Heightmap\Heightmap.h"
#include "Algorithms\Perlin Noise\PerlinNoise.h"
#include "Algorithms\MidPointDisplacement\MidPointDisplacement.h"
#include "Algorithms\Voronoi\VoronoiDiagram.h"
#include "Algorithms\Eroders\Thermal\ThermalEroder.h"
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

	constexpr int exponent = 9;

	srand(time(NULL)); //TODO: meter inicialización a la libreria para esto

	Heightmap h_mpd(exponent);

	MidPointDisplacement::MidPointProperties mdp_p(0.3f, 0.5f);
	
	MidPointDisplacement mpd(mdp_p);

	mpd.GenerateHeightmap(h_mpd);

	h_mpd.DumpToFile("MixedHeightmaps/MidPoint");

	std::cout << "Mid point genereado" << std::endl;
	//_getch();



	/*------------------------------------------------------------------------------------------*/
	
	Heightmap h_voronoi(exponent);
	VoronoiDiagram::VoronoiProperties voronoi_p(10, 0.8f, 0.2f);
	VoronoiDiagram voronoi(voronoi_p);

	voronoi.GenerateHeightmap(h_voronoi);
	h_voronoi.DumpToFile("MixedHeightmaps/Voronoi");
	std::cout << "Voronoi genereado" << std::endl;
	


	/*-----------------------------------------------------------------------------------------*/

	Heightmap h_copy(h_mpd);

	tools::MixHeightmaps(h_mpd, h_voronoi, 0.5f, 0.0f);
	tools::MixHeightmaps(h_copy, h_voronoi, 0.5f, 0.5f);

	//PrintHeightMap(h_mpd);
	h_mpd.DumpToFile("MixedHeightmaps/MixedHeightmapNoPerturbation");
	h_copy.DumpToFile("MixedHeightmaps/MixedHeightmapPerturbated");

	std::cout << "Heigthmaps mezclados" << std::endl;

	//_getch();

	/*------------------------------------------------------------------------------------------*/

	
	ErosionProperties erosion(ErosionType::THERMAL);
	
	

	ErodeHeightmap(h_copy, erosion);

	h_copy.DumpToFile("Eroded");

	return 0;
}