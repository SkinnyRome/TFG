#ifndef MIDPOINTDIPLACEMENT_H
#define MIDPOINTDISPLACEMENT_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <algorithm>

class Heightmap;

class TERRAINGENERATOR_API MidPointDisplacement
{

public:

	struct TERRAINGENERATOR_API Properties {
	
		
		Properties(float vSpread = 0.3f, float vRoughness = 0.5f);

		float spread;
		float roughness;

	};

	MidPointDisplacement();
	MidPointDisplacement(const Properties p);
	~MidPointDisplacement();

	void GenerateHeightmap(Heightmap& h) const;

private:
	
	Properties prop;

	float Jitter(float value, float spread) const ;
	int MidPoint(int a, int b) const;
	void MidPointDisplace(Heightmap &h, int lx, int rx, int ty, int by, float spread) const;

};

#endif //MIDPOINTDISPLACEMENT_H