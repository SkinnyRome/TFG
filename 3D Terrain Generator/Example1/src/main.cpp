#include <time.h>
#include <iostream>
#include <fstream> 
#include <random>
#include <conio.h>
#include "Heightmap\Heightmap.h"
#include "Algorithms\Perlin Noise\PerlinNoise.h"
#include "Algorithms\MidPointDisplacement\MidPointDisplacement.h"
#include <Tools\TerrainGenerationTools.h>

using namespace std;

void PrintHeightMap(const Heightmap& h) {

	if (h.GetWidth() > 9 || h.GetHeight() > 9)
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


	srand(time(NULL));

	Heightmap h_mpd(3);
	MidPointDisplacement::MidPointProperties mdp_p(0.5f, 0.5f);
	MidPointDisplacement mpd(mdp_p);

	mpd.GenerateHeightmap(h_mpd);

	//h_mpd.DumpToFile("PruebaMidPoint");

	PrintHeightMap(h_mpd);


	//_getch();



	/*------------------------------------------------------------------------------------------*/




	Heightmap h_pn(9, 9);
	//PerlinNoise::PNProperties perlin_pn(2500);
	//PerlinNoise pn(perlin_pn);

	//pn.GenerateHeightmap(h_pn);

	//h_pn.DumpToFile("PruebaPerlin");

	//PrintHeightMap(h_pn);

	//_getch();

	/*-----------------------------------------------------------------------------------------*/

	//tools::MixHeightmaps(h_mpd, h_pn, 0.5f);

	//PrintHeightMap(h_mpd);

	_getch();

	return 0;
}