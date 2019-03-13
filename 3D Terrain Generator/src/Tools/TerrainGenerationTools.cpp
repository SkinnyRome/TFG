#include <Heightmap\Heightmap.h>
#include "TerrainGenerationTools.h"

using namespace tools;


#pragma region Point
Point::Point() :x(0), y(0) {};

Point::Point(float x, float y) : x(x), y(y) {}

Point::Point(const Point& p) {
	x = p.x;
	y = p.y;
}

float Point::operator*(const Point& p) {

	return (x * p.x) + (y * p.y);
}

Point Point::operator*(const float t) {
	return Point(x*t, y*t);
}

Point Point::operator/(const Point& p) {
	return Point(x / p.x, y / p.y);
}

Point Point::operator-(const Point& p) {
	return Point(x - p.x, y - p.y);
}

Point tools::Point::operator-(const Point & p) const
{
	return Point();
}


Point Point::operator+(const Point& p) {
	return Point(x + p.x, y + p.y);
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

void tools::MixHeightmaps(Heightmap & h1, const Heightmap & h2, float influence)
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


	h1.Normalize();

}



#pragma endregion