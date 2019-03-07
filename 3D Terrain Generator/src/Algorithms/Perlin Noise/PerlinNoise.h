#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <Heightmap\Heightmap.h>
#include <random>
#include <numeric>

class PerlinNoise
{
private:
	//Mover esto a la clase base Algoritmo para que no se pueda copiar
	PerlinNoise(const PerlinNoise&);
	PerlinNoise& operator=(const PerlinNoise&) {};


	std::vector<int> p; //permutation vector
	int _seed;

	float Gradient(int hash, float x, float y);
	float Fade(float t);
	float LinearInterpolation(float a, float b, float t);
	float Noise(float x, float y);

public:
	PerlinNoise();
	PerlinNoise(int seed);
	~PerlinNoise();

	void GenerateHeightmap(Heightmap &h);
};

#endif