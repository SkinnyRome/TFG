#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <vector>
#include <Tools\TerrainGenerationTools.h>

class Heightmap;

class TERRAINGENERATOR_API VoronoiDiagram
{

public:

	class  TERRAINGENERATOR_API VoronoiProperties {
	public:
		VoronoiProperties();
		VoronoiProperties(int nSites, float fallOff, float dropOff);

		int numOfSites;
		float fallOff;
		float dropOff;
	};

	VoronoiDiagram(const VoronoiProperties p);
	~VoronoiDiagram();

	void GenerateHeightmap(Heightmap &h);

private:


	VoronoiProperties _properties;
	std::vector<float> _sitesCoefficients;
	tools::Point CreateRandomSite(const Heightmap &h);

};

#endif