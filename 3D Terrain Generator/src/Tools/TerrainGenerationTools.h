#ifndef TERRAINGENERATIONTOOLS_H
#define TERRAINGENERATIONTOOLS_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif


class Heightmap;

namespace  tools {

	struct Point {

		Point();

		Point(float x, float y);

		Point(float p);

		Point(const Point& p);

		float modulo();

		float x;
		float y;

	};


	const float operator*(const Point& lhp, const Point& rhp);

	const Point operator/(const Point& lhp, const Point& rhp);

	const Point operator-(const Point& lhp, const Point& rhp);

	const Point operator+(const Point& lhp, const Point& rhp);

	//Definition
	TERRAINGENERATOR_API float GetRandomValueBetween(float a, float b);

	//Definition
	TERRAINGENERATOR_API float Average2(float a, float b);

	//Definition
	TERRAINGENERATOR_API float Average4(float a, float b, float c, float d);

	//Definition
	TERRAINGENERATOR_API void MixHeightmaps(Heightmap &h1, const Heightmap &h2, float influence, float perturbation);

	//Definition
	void ApplyFilter(Heightmap &h1, int magnitude = 5);
}


#endif //TERRAINGENERATIONTOOLS_H