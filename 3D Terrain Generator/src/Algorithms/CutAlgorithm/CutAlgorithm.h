#ifndef CUTALGORITHM_H
#define CUTALGORITHM_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <Tools\TerrainGenerationTools.h>
#include <vector>

class Heightmap;
using namespace tools;


using PuntosYValor = std::pair<std::pair<Point, Point>, float>;

class TERRAINGENERATOR_API CutAlgorithm
{
public:
	CutAlgorithm();
	~CutAlgorithm();

	void GenerateHeightmap(Heightmap& h);

private:

	Point ClosestPointOnSegment(const Point& a, const Point& b, const Point& p);
	void DoCuts(const std::vector<PuntosYValor> &v, Heightmap &h);
	PuntosYValor RandomCut(int axis, int width, int height);

};

#endif //CUTALGORITHM_H