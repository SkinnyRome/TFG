#include <Heightmap\Heightmap.h>
#include <random>
#include <chrono>
#include "TerrainGenerationTools.h"
#include <algorithm>
#include <Algorithms\Perlin Noise\PerlinNoise.h>


using namespace tools;


#pragma region Point

Point::Point() :x(0), y(0) {};

Point::Point(float x, float y) : x(x), y(y) {}

tools::Point::Point(float p): x(p), y (p){}

Point::Point(const Point& p):x(p.x), y(p.y) {}

const float tools::operator*(const Point& rhp, const Point& lhp) {

	return (rhp.x * lhp.x) + (rhp.y * lhp.y);
}


const tools::Point tools::operator/(const Point& lhp, const Point& rhp) {
	return Point(lhp.x / rhp.x, lhp.y / rhp.y);
}

const Point tools::operator-(const Point& lhp, const Point& rhp) {
	return Point(lhp.x - rhp.x, lhp.y - rhp.y);
}


const Point tools::operator+(const Point& lhp, const Point& rhp) {
	return Point(lhp.x + rhp.x, lhp.y + rhp.y);
}

float Point::modulo() {
	float xPow = (float)pow(x, 2);
	float yPow = (float)pow(y, 2);
	return xPow + yPow;
}

#pragma endregion

#pragma region Functions
float tools::GetRandomValueBetween(float a, float b)
{
	return a + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (b - a)));
}

float tools::Average2(float a, float b) {

	return (a + b) / 2;

};

float tools::Average4(float a, float b, float c, float d) {
	
	return (a + b + c + d) / 4;

}

Heightmap tools::MixHeightmaps(const Heightmap & h1, const Heightmap & h2, float influence, float perturbation)
{


	//TODO: forzar a que el valor de influence est� entre [0.0f, 1.0f]
	if (influence < 0.0f || influence > 1.0f)
		return h1;
	//Forzar que los heightmap sean iguale
	if (h1.GetSize() != h2.GetSize())
		return h1;

	float h2Influence = influence;
	float h1Influence = 1.0f - influence;

	float width = h1.GetSize();
	float height = h1.GetSize();


	Heightmap result{static_cast<int>(h1.GetExponent()) };


	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			result[i][j] = (h1[i][j] * h1Influence) + (h2[i][j] /**  h2Influence*/);

			
			
		}

	}

	int magnitude = static_cast<int>((0.5f * width) * perturbation);
	
	ApplyFilter(result, magnitude);
	

	//TODO return un Heightmap para optimizar las cosas
	return result;

}

void tools::ApplyFilter(Heightmap & h, int magnitude)
{
	Heightmap copy(h);

	Heightmap x_perturbation( h.GetExponent());
	Heightmap y_perturbation( h.GetExponent());

	PerlinNoise perlin;

	perlin.GenerateHeightmap(x_perturbation);
	perlin.GenerateHeightmap(y_perturbation);


	int xIndex, yIndex, xRandDisplacement, yRandDisplacement;

	for (int i = 0; i < h.GetSize(); i++) {
		for (int j = 0; j < h.GetSize(); j++) {

			xRandDisplacement = (round((magnitude * (x_perturbation[i][j] - 0.5f))));
			yRandDisplacement = (round((magnitude * (y_perturbation[i][j] - 0.5f))));

			xIndex = static_cast<int>(abs(i + xRandDisplacement));
			xIndex = (xIndex >= h.GetSize()) ? xIndex - (xIndex - h.GetSize()) -1 : xIndex;
		

			yIndex = static_cast<int>(abs(j + yRandDisplacement));
			yIndex = (yIndex >= h.GetSize()) ? yIndex - (yIndex - h.GetSize()) - 1 : yIndex;

			//TODO: hacer que cuando un �ndice se salga de la matriz, ponerlo al m�ximo para que no de la vuelta, que queda mal.
			h[i][j] = copy[xIndex][yIndex];			

		}

	}

	h.Normalize();
}

void tools::GenerateRandomNoise(Heightmap &h)
{
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(0.5f, 0.25f);

	for (int i = 0; i < h.GetSize(); i++) {
		for (int j = 0; j < h.GetSize(); j++) {
			//h[i][j] = tools::GetRandomValueBetween(0.0f, 1.0f);
			h[i][j] = distribution(generator);
		}
	}

	h.Normalize();
}

void tools::RandomizeSeed() {


	int randSeed = static_cast<int>(std::chrono::duration_cast<std::chrono::minutes>(
		std::chrono::system_clock::now().time_since_epoch()).count());
	srand(randSeed);

}
#pragma endregion