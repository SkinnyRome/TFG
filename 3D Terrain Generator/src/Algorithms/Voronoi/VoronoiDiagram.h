#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <vector>
#include <Tools\TerrainGenerationTools.h>
#include "..\IAlgorithm.h"


class Heightmap;

class TERRAINGENERATOR_API VoronoiDiagram : public IAlgorithm
{
public:

	/*Number of sites: default 1
	  Slope softness: default 1.0f
	  Distance between: default 0.0f
	  Average height: default 1.0f
	*/
	struct  TERRAINGENERATOR_API Properties {
		Properties(int nSites, float sSlope = default_properties.slope_softness,
			float dist = default_properties.distance_between,
			float aHeight = default_properties.average_height);

		int numOfSites;
		float slope_softness;
		float distance_between;
		float average_height;
	};

	VoronoiDiagram(Properties p);

	void GenerateHeightmap(Heightmap &h) const;

private:

	static Properties default_properties;

	Properties prop;
	std::vector<float> _sitesCoefficients;
	tools::Point CreateRandomSite(const Heightmap &h) const;

};

#endif