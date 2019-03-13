#ifndef TERRAINGENERATIONTOOLS_H
#define TERRAINGENERATIONTOOLS_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <algorithm>

class Heightmap;

namespace  tools {

	struct Point {

		Point();

		Point(float x, float y);

		Point(const Point& p);

		float operator*(const Point& p);

		Point operator*(const float t);

		Point operator/(const Point& p);

		Point operator-(const Point& p);

		Point operator-(const Point& p) const;

		Point operator+(const Point& p);

		float modulo();

		float x;
		float y;

	};


	TERRAINGENERATOR_API float GetRandomValueBetween(float a, float b);
	TERRAINGENERATOR_API float Average2(float a, float b);
	TERRAINGENERATOR_API float Average4(float a, float b, float c, float d);

	TERRAINGENERATOR_API void MixHeightmaps(Heightmap &h1, const Heightmap &h2, float influence);


}


#endif //TERRAINGENERATIONTOOLS_H