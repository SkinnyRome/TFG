#include "DiamondSquare.h"
#include <Heightmap\Heightmap.h>
#include <Tools\TerrainGenerationTools.h>


DiamondSquare::Properties DiamondSquare::default_properties = { 0.3f, 0.5f };


DiamondSquare::DiamondSquare(Properties p):prop(p)
{
}

void DiamondSquare::GenerateHeightmap(Heightmap & h) const
{

	//1. Initialize the corners of the heightmap with random values (between 0.0 and 1.0)
	h[0][0] = tools::GetRandomValueBetween(0.0f, 1.0f);					//Top-left corner
	h[h.GetSize() - 1][0] = tools::GetRandomValueBetween(0.0f, 1.0f); ;			//Top-right corner
	h[0][h.GetSize() - 1] = tools::GetRandomValueBetween(0.0f, 1.0f); ;	//Bot-left corner
	h[h.GetSize() -1][h.GetSize() - 1] =tools::GetRandomValueBetween(0.0f, 1.0f); ;	//Bot-right corner

																	//Calculate the iterations needed to compute all the points (equal to exponent value)
	int iterations = h.GetExponent(); //TODO comprobar que el heightmap es cuadrado

	if (iterations <= 0)//TODO EXCEPCIÓN
		return;

	//Values used to randomize the variation added to a point
	float auxSpread = prop.spread;
	

	for (int i = 0; i < iterations; i++) {

		//Calculate the number of blocks in this iteration (2 pow i)
		int blocks = static_cast<int>(pow(2, i));

		//Calculate the width of each block
		int blockSize = (h.GetSize() - 1) / blocks;

		//Get the corners of every block and call MidPointDisplace 
		for (int x = 0; x < blocks; x++) {
			for (int y = 0; y < blocks; y++) {

				int left_x = (blockSize * x);
				int right_x = (left_x + blockSize);
				int top_y = (blockSize * y);
				int bottom_y = (top_y + blockSize);

				MidPointDisplace(h, left_x, right_x, top_y, bottom_y, auxSpread);

			}
		}

		//Reduce the spread value
		auxSpread *= prop.roughness;

	}

	//Normalize values of the heightmap so they are between [0.0, 1.0]
	h.Normalize();

}



float DiamondSquare::Jitter(float value, float spread) const
{
	return value += tools::GetRandomValueBetween(-spread, spread);
}

int DiamondSquare::MidPoint(int a, int b) const
{
	return (a + b) / 2;
}


void DiamondSquare::MidPointDisplace(Heightmap & h, int lx, int rx, int ty, int by, float spread) const
{
	//Obtain the axis center points of the block
	int cx = MidPoint(lx, rx);
	int cy = MidPoint(ty, by);

	//Get the values of the corner of the block in the heightmap
	float top_left = h[lx][ty];
	float top_right = h[rx][ty];
	float bottom_left = h[lx][by];
	float bottom_right = h[rx][by];

	//Calculate the average and add them a random value
	float top = tools::Average2(top_left, top_right);
	float left = tools::Average2(top_left, bottom_left);
	float bottom = tools::Average2(bottom_left, bottom_right);
	float right = tools::Average2(top_right, bottom_right);
	float center = tools::Average4(top, left, bottom, right);

	h[cx][by] = Jitter(bottom, spread);
	h[cx][ty] = Jitter(top, spread);
	h[lx][cy] = Jitter(left, spread);
	h[rx][cy] = Jitter(right, spread);
	h[cx][cy] = Jitter(center, spread);
}



DiamondSquare::Properties::Properties(float s, float r)
{
	spread = (s > 1.0f || s < 0) ? default_properties.spread : s;

	roughness = ((r > 1.0f || r < 0.0f) ? default_properties.roughness : r);

}


