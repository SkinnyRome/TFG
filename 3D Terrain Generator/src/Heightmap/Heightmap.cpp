#include "Heightmap.h"
#include <Tools\TerrainGenerationTools.h>
#include <fstream>




Heightmap::Heightmap(int exp):_exponent(exp)
{
	if (_exponent > 10)
	{
		//Default size = 2pow8
		_exponent = 8;
	}
	_size = static_cast<int>(pow(2, _exponent)) + 1;
	_heightmap = vector<vector<float>>(_size, vector<float>(_size));
}


Heightmap Heightmap::operator+(const float a)
{
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			_heightmap[i][j] += a;
		}
	}
	return *this;
}

inline Heightmap Heightmap::operator*(const float a)
{
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			_heightmap[i][j] *= a;
		}
	}
	return *this;
}


void Heightmap::Resize(int width, int height)
{

	_size = width;
	_size = height;

	_heightmap.resize(width);
	for (std::vector<float> & h : _heightmap) {
		h.resize(height);
	}

}

void Heightmap::Resize(int exponent)
{
	_exponent = (exponent <= 0 || exponent > 10) ? 8 : exponent ;
	_size = static_cast<int>(pow(2, exponent));
	_size = _size;
	Resize(_size, _size);
}

void Heightmap::Normalize()
{
	//TODO: problema, si normalizamos siempre, casi siempre va a haber un punto que valga 1.0f
	float min = _heightmap[0][0];
	float max = _heightmap[0][0];

	//bool need_normalize = false;

	//Get the max and the min values of the heightmap
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {

			float value = _heightmap[i][j];

			if (value > max) {
				max = value;
			}
			if (value < min) {
				min = value;
			}
		}

	}

#ifdef _DEBUG
	//cout << "Max " << max << " Min " << min << endl;
#endif

	//Normalize
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {

			float value = _heightmap[i][j];

			_heightmap[i][j] = (value - min) / (max - min);

		}
	}
}

void Heightmap::DumpToFile(string filename, RawMode mode)
{

	string filepath("../HeightMaps/" + filename + ".raw");


	std::ofstream rawFile;
	rawFile.open(filepath, std::fstream::binary | std::fstream::out);

	if (!rawFile.is_open())
		std::cout << "No se ha podido crear el archivo" << std::endl;



	for (int j = 0; j < _size; j++) {
		for (int i = 0; i < _size; i++) {
			unsigned short int value(tools::FloatToShortInt(_heightmap[i][j]));
			rawFile.write(reinterpret_cast<const char*>(&value), sizeof(unsigned short int));
		}
	}


	rawFile.close();


}

inline TERRAINGENERATOR_API Heightmap operator+(const Heightmap & lhh, const Heightmap & rhh)
{

	if (lhh.GetSize() != rhh.GetSize()) {
		throw std::length_error{ "The heightmaps size are diferent" };
	}



	Heightmap heightmap_add(lhh.GetSize());
	for (int i = 0; i < lhh.GetSize(); i++) {
		for (int j = 0; j < lhh.GetSize(); j++) {
			heightmap_add[i][j] = lhh[i][j] + rhh[i][j];
		}
	}

	return heightmap_add;
}

inline TERRAINGENERATOR_API Heightmap operator-(const Heightmap & lhh, const Heightmap & rhh)
{
	if (lhh.GetSize() != rhh.GetSize()) {
		throw std::length_error{ "The heightmaps size are diferent" };
	}

	Heightmap heightmap_add(lhh.GetSize());
	for (int i = 0; i < lhh.GetSize(); i++) {
		for (int j = 0; j < lhh.GetSize(); j++) {
			heightmap_add[i][j] = lhh[i][j] - rhh[i][j];
		}
	}

	return heightmap_add;
}
