#include "PerlinNoise.h"
#include <time.h>

using namespace std;

PerlinNoise::PerlinNoise(Properties p):prop(p)
{
	srand(time(NULL));

}


PerlinNoise::~PerlinNoise()
{
}

void PerlinNoise::GenerateHeightmap(Heightmap & h)
{
	//Create and initialize random vector values
	p.resize(256);
	iota(p.begin(), p.end(), 0);
	mt19937 g(prop._seed);
	shuffle(p.begin(), p.end(), g);

	// Duplicate the permutation vector
	p.insert(p.end(), p.begin(), p.end());


	for (int i = 0; i < h.GetWidth(); i++) {
		for (int j = 0; j < h.GetHeight(); j++) {
			float x = (float)i / ((float)h.GetWidth());
			float y = (float)j / ((float)h.GetHeight());

			//Typical
			float n = Noise(10 * x, 10 * y);

			//Wood
			//float n = 20 * noise(x,y);
			//n = n - floor(n);

			h[i][j] = n;

		}
	}


}

float PerlinNoise::Fade(float t) {

	return t * t * t * (t *(t * 6 - 15) + 10);

}

float PerlinNoise::LinearInterpolation(float a, float b, float t) {
	return a + t * (b - a);
}


//Calculates a dot product between the vector x, y and a pseudo random gradient vector.
float PerlinNoise::Gradient(int hash, float x, float y) {

	return ((hash & 1) ? x : -x) + ((hash & 2) ? y : -y);

}

float PerlinNoise::Noise(float x, float y) {

	//Find the pixel cell
	int cellX = (int)floor(x) & /*(GRID_SIZE - 1)*/ 255;
	int cellY = (int)floor(y) & /*(GRID_SIZE - 1)*/ 255;

	int cellX1 = (cellX + 1) & 255;
	int cellY1 = (cellY + 1) & 255;


	//Find the relative x, y of point in cube
	x -= floor(x);
	y -= floor(y);

	float u = Fade(x);
	float v = Fade(y);

	//Hash coordinates for the four corners of our grid cell (p[p[x] + y])
	int left_top_corner = p[p[cellX] + cellY];
	int right_top_corner = p[p[cellX1] + cellY];
	int left_bot_corner = p[p[cellX] + cellY1];
	int right_bot_corner = p[p[cellX1] + cellY1];

	//Obtain the dot products between the random gradients and the vectors pointing to P (x,y)
	float left_top_grad = Gradient(left_top_corner, x, y);
	float right_top_grad = Gradient(right_top_corner, x - 1, y);
	float left_bot_grad = Gradient(left_bot_corner, x, y - 1);
	float right_bot_grad = Gradient(right_bot_corner, x - 1, y - 1);

	//Interpolate
	float x1 = LinearInterpolation(left_top_grad, right_top_grad, u);
	float x2 = LinearInterpolation(left_bot_grad, right_bot_grad, u);
	float r = LinearInterpolation(x1, x2, v);

	return (r + 1.0f) / 2.0f;
}


PerlinNoise::Properties::Properties(int seed):_seed(seed)
{
}
