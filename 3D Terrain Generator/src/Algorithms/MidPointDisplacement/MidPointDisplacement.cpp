#include "MidPointDisplacement.h"
#include <Heightmap\Heightmap.h>
#include <Tools\TerrainGenerationTools.h>


MidPointDisplacement::MidPointDisplacement():_properties(MidPointProperties())
{
}

MidPointDisplacement::MidPointDisplacement(const MidPointProperties p):_properties(p)
{
}


MidPointDisplacement::~MidPointDisplacement()
{
}


void MidPointDisplacement::GenerateHeightmap(Heightmap & h)
{
	//1. Initialize the corners of the heightmap with random values (between 0.0 and 1.0)
	h[0][0] = tools::GetRandomValueBetween(0.0f, 1.0f);					//Top-left corner
	h[h.GetWidth() - 1][0] = tools::GetRandomValueBetween(0.0f, 1.0f); ;			//Top-right corner
	h[0][h.GetHeight() - 1] = tools::GetRandomValueBetween(0.0f, 1.0f); ;	//Bot-left corner
	h[h.GetWidth() -1][h.GetHeight() - 1] =tools::GetRandomValueBetween(0.0f, 1.0f); ;	//Top-left corner

																	//Calculate the iterations needed to compute all the points (equal to exponent value)
	int iterations = h.GetExponent(); //TODO comprobar que el heightmap es cuadrado

	if (iterations <= 0)//TODO EXCEPCIÓN
		return;

	//Values used to randomize the variation added to a point
	float auxSpread = _properties.spread;
	

	for (int i = 0; i < iterations; i++) {

		//Calculate the number of blocks in this iteration (2 pow i)
		int blocks = static_cast<int>(pow(2, i));

		//Calculate the width of each block
		int blockSize = (h.GetWidth() - 1) / blocks;

		//Get the corners of every block and call MidPointDisplace 
		for (int x = 0; x < blocks; x++) {
			for (int y = 0; y < blocks; y++) {

				int left_x = (blockSize * x);
				int right_x = (left_x + blockSize);
				int bottom_y = (blockSize * y);
				int top_y = (bottom_y + blockSize);

				MidPointDisplace(h, left_x, right_x, top_y, bottom_y, auxSpread);

			}
		}

		//Reduce the spread value
		auxSpread *= _properties.roughness;

	}

	//Normalize values of the heightmap so they are between [0.0, 1.0]
	h.Normalize();



}



float MidPointDisplacement::Jitter(float value, float spread) const
{
	return value += tools::GetRandomValueBetween(-spread, spread);
}

int MidPointDisplacement::MidPoint(int a, int b) const
{
	return (a + b) / 2;
}


void MidPointDisplacement::MidPointDisplace(Heightmap & h, int lx, int rx, int ty, int by, float spread) const
{
	//Obtain the axis center points of the block
	int cx = MidPoint(lx, rx);
	int cy = MidPoint(ty, by);

	//Get the values of the corner of the block in the heightmap
	float top_left = h[ty][lx];
	float top_right = h[ty][rx];
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

void MidPointDisplacement::SetRandomValues(Heightmap &h) const
{
	for (int i = 0; i < h.GetWidth(); i++) {
		for (int j = 0; j < h.GetHeight(); j++) {
			h[i][j] = tools::GetRandomValueBetween(0.0f, 1.0f);
		}
	}
}

MidPointDisplacement::MidPointProperties::MidPointProperties():spread(0.3f), roughness(0.5f)
{
}

MidPointDisplacement::MidPointProperties::MidPointProperties(float s, float r): spread(s), roughness(r)
{
}


