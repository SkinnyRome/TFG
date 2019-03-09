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



#pragma endregion