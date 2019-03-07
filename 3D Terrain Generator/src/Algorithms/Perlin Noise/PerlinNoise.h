#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <Heightmap\Heightmap.h>
#include <random>
#include <numeric>


class PerlinNoise
{
public:

	class PNProperties {
		public:

			PNProperties();
			PNProperties(int seed);

			int _seed;
			
	};

private:
	//Mover esto a la clase base Algoritmo para que no se pueda copiar
	PerlinNoise(const PerlinNoise&);
	PerlinNoise& operator=(const PerlinNoise&) {};


	std::vector<int> p; //permutation vector
	PNProperties _properties;

	float Gradient(int hash, float x, float y);
	float Fade(float t);
	float LinearInterpolation(float a, float b, float t);
	float Noise(float x, float y);

public:

	//PerlinNoise();
	explicit PerlinNoise(PNProperties properties = PNProperties());
	~PerlinNoise();

	void GenerateHeightmap(Heightmap &h);
};

#endif