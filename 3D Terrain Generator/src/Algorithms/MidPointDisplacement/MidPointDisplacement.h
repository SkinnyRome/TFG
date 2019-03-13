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

	class TERRAINGENERATOR_API MidPointProperties {
	public:
		MidPointProperties();
		MidPointProperties(float s, float r);

		float spread;
		float roughness;

	};

	MidPointDisplacement();
	MidPointDisplacement(const MidPointProperties p);
	~MidPointDisplacement();

	void GenerateHeightmap(Heightmap& h);

private:
	
	MidPointProperties _properties;

	float Jitter(float value, float spread)const ;
	int MidPoint(int a, int b)const ;
	void MidPointDisplace(Heightmap &h, int lx, int rx, int ty, int by, float spread) const;
	void SetRandomValues(Heightmap& h) const;

};

#endif //MIDPOINTDISPLACEMENT_H