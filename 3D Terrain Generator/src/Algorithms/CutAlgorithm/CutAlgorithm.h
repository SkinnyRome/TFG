#ifndef CUTALGORITHM_H
#define CUTALGORITHM_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <vector>
#include <Tools\TerrainGenerationTools.h>

using namespace tools;
class Heightmap;

using Cut = std::pair<std::pair<Point, Point>, std::pair<float,float>>;

class TERRAINGENERATOR_API CutAlgorithm
{
public:

	struct TERRAINGENERATOR_API Properties {
	
		Properties(int nSlopes = default_properties.num_of_slopes, float fRoughness = default_properties.roughness);

		int num_of_slopes;
		float roughness;
	};

	CutAlgorithm(Properties p = Properties{});

	void CutHeightmap(Heightmap& h) const;

	void SetProperties(Properties p);

	Properties GetProperties() const;

private:

	static Properties default_properties;

	Properties prop;

	Point ClosestPointOnSegment(const Point& a, const Point& b, const Point& p) const;
	void DoCuts(const std::vector<Cut> &v, Heightmap &h) const;
	Cut CreateRandomCut (const int width, const int height) const;

};

#endif //CUTALGORITHM_H