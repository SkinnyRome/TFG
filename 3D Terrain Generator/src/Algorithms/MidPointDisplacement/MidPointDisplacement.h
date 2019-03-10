#ifndef MIDPOINTDIPLACEMENT_H
#define MIDPOINTDISPLACEMENT_H

#include <algorithm>


class Heightmap;

class MidPointDisplacement
{

public:

	class MidPointProperties {
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