#ifndef DIAMONDSQUARE_H
#define DIAMONDSQUARE_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <algorithm>
#include "..\IAlgorithm.h"

class Heightmap;

class TERRAINGENERATOR_API DiamondSquare : public IAlgorithm
{

public:

	struct TERRAINGENERATOR_API Properties {
	
		Properties(float vSpread = default_properties.spread, float vRoughness = default_properties.roughness);

		float spread;
		float roughness;

	};

	DiamondSquare(Properties p = {});

	void GenerateHeightmap(Heightmap& h) const;

private:
	
	static Properties default_properties;

	Properties prop;

	float Jitter(float value, float spread) const ;
	int MidPoint(int a, int b) const;
	void MidPointDisplace(Heightmap &h, int lx, int rx, int ty, int by, float spread) const;

};

#endif //DiamondSquare_H