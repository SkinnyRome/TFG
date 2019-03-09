#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H

#include <Tools\TerrainGenerationTools.h>

class Heightmap;

class VoronoiDiagram
{

public:

	class VoronoiProperties {
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