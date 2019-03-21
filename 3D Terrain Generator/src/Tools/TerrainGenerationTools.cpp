#include <Heightmap\Heightmap.h>
#include "TerrainGenerationTools.h"
#include <algorithm>
#include <Algorithms\MidPointDisplacement\MidPointDisplacement.h>
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

void tools::MixHeightmaps(Heightmap & h1, const Heightmap & h2, float influence, float perturbation)
{

	

	//TODO: forzar a que el valor de influence esté entre [0.0f, 1.0f]

	int hWidth = h2.GetWidth();
	int hHeight = h2.GetHeight();

	bool isSquare = h2.IsSquare();

	//First, resize the heightmaps.
	if (h1.GetWidth() != hWidth || h1.GetHeight() != hHeight) {
		if (isSquare)
			h1.Resize(h2.GetExponent());
		else
			h1.Resize(hWidth, hHeight);
	}

	float h2Influence = influence;
	float h1Influence = 1.0f - influence;


	for (int i = 0; i < hWidth; i++) {
		for (int j = 0; j < hHeight; j++) {
			h1[i][j] = (h1[i][j] * h1Influence) + (h2[i][j] *  h2Influence);
			
		}

	}

	int magnitude = static_cast<int>((0.5f * h1.GetWidth()) * perturbation);
	
	ApplyFilter(h1, magnitude);
	

	//TODO return un Heightmap para optimizar las cosas


}

void tools::ApplyFilter(Heightmap & h, int magnitude)
{

	Heightmap copy(h);

	Heightmap hMpd1(h.GetExponent());
	Heightmap hMpd2(h.GetExponent());

	MidPointDisplacement::MidPointProperties mdp_p(0.3f, 0.5f);

	MidPointDisplacement mpd(mdp_p);

	mpd.GenerateHeightmap(hMpd1);
	mpd.GenerateHeightmap(hMpd2);

	int xIndex, yIndex, xRandDisplacement, yRandDisplacement;

	for (int i = 0; i < h.GetWidth(); i++) {
		for (int j = 0; j < h.GetHeight(); j++) {

			xRandDisplacement = (round((magnitude * (hMpd1[i][j] - 0.5f))));
			yRandDisplacement = (round((magnitude * (hMpd2[i][j] - 0.5f))));

			xIndex = static_cast<int>(abs(i + xRandDisplacement));
			xIndex = (xIndex >= h.GetWidth()) ? xIndex - (xIndex - h.GetWidth()) -1 : xIndex;
		

			yIndex = static_cast<int>(abs(j + yRandDisplacement));
			yIndex = (yIndex >= h.GetHeight()) ? yIndex - (yIndex - h.GetHeight()) - 1 : yIndex;

			//TODO: hacer que cuando un índice se salga de la matriz, ponerlo al máximo para que no de la vuelta, que queda mal.
			h[i][j] = copy[xIndex][yIndex];			


		}


	}

	h.Normalize();
}



#pragma endregion