#include <iostream>
#include <fstream> 
#include <conio.h>
#include "Heightmap\Heightmap.h"
#include "Algorithms\Perlin Noise\PerlinNoise.h"
#include "Algorithms\MidPointDisplacement\MidPointDisplacement.h"
#include "Algorithms\Voronoi\VoronoiDiagram.h"
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


	Heightmap h_mpd(8);

	MidPointDisplacement::MidPointProperties mdp_p(0.3f, 0.5f);
	
	MidPointDisplacement mpd(mdp_p);

	mpd.GenerateHeightmap(h_mpd);

	h_mpd.DumpToFile("MidPoint");

	std::cout << "Mid point genereado" << std::endl;
	//_getch();



	/*------------------------------------------------------------------------------------------*/
	
	Heightmap h_voronoi(257,257);
	VoronoiDiagram::VoronoiProperties voronoi_p(10, 0.8f, 0.2f);
	VoronoiDiagram voronoi(voronoi_p);

	voronoi.GenerateHeightmap(h_voronoi);
	std::cout << "Voronoi genereado" << std::endl;
	

	h_voronoi.DumpToFile("Voronoi2");

	/*-----------------------------------------------------------------------------------------*/

	tools::MixHeightmaps(h_mpd, h_voronoi, 0.67f);

	//PrintHeightMap(h_mpd);

	h_mpd.DumpToFile("MixedHeightmap");

	//_getch();

	return 0;
}