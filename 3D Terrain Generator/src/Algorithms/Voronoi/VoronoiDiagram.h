#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <Tools\TerrainGenerationTools.h>

class Heightmap;

class TERRAINGENERATOR_API VoronoiDiagram
{

public:

	class  TERRAINGENERATOR_API VoronoiProperties {
	public:
		VoronoiProperties();
		VoronoiProperties(int nOS, float fO, float dO);

		int numOfSites;
		float fallOff;
		float dropOff;
	};

	VoronoiDiagram(const VoronoiProperties p);
	~VoronoiDiagram();

	void GenerateHeightmap(Heightmap &h);

private:


	VoronoiProperties _properties;
	tools::Point CreateRandomSite(const Heightmap &h);

};

#endif