#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <Heightmap\Heightmap.h>
#include "..\IAlgorithm.h"
#include <random>
#include <numeric>

//using NoiseFunction = float(*)(float x, float y);


class TERRAINGENERATOR_API PerlinNoise :  public IAlgorithm
{
public:

	struct TERRAINGENERATOR_API Properties {
		public:
			Properties(int seed = 0);

			int _seed;
			
	};

private:
	//Mover esto a la clase base Algoritmo para que no se pueda copiar
	PerlinNoise(const PerlinNoise&);
	PerlinNoise& operator=(const PerlinNoise&) = default;


	std::vector<int> p; //permutation vector
	Properties prop;

	float Gradient(int hash, float x, float y);
	float Fade(float t);
	float LinearInterpolation(float a, float b, float t);
	float Noise(float x, float y);

public:

	PerlinNoise(Properties properties = Properties{});
	~PerlinNoise();

	void GenerateHeightmap(Heightmap &h) const;
};

#endif