#include "Heightmap.h"
#include <Tools\TerrainGenerationTools.h>
#include <fstream>


void Heightmap::CalculateExponent()
{
	//Find if it's power of 2 and its exponent.
	if (_width == _height) {
		int size = _width;
		int exp = 0;
		if (size > 0)
		{
			while (size % 2 == 0)
			{
				size /= 2;
				++exp;
			}
			if (size == 1)
			{
				_exponent = exp;
			}
		}
		if (size == 0 || size != 1)
		{
			_exponent = -1;
		}
	}
	else
		_exponent = -1;
}



Heightmap::Heightmap(int width, int height):_exponent(0), _width(width), _height(height), _heightmap(_width, vector<float>(_height))
{
	CalculateExponent();
}

Heightmap::Heightmap(int exponent):_exponent(exponent), _width(static_cast<int>(pow(2,_exponent)) + 1), _height(_width), _heightmap(_width, vector<float>(_height))
{
	
}


Heightmap Heightmap::operator+(const float a)
{
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {
			_heightmap[i][j] += a;
		}
	}
	return *this;
}

inline Heightmap Heightmap::operator*(const float a)
{
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {
			_heightmap[i][j] *= a;
		}
	}
	return *this;
}

bool Heightmap::IsSquare() const
{
	return _width == _height;
}

bool Heightmap::IsPowerOfTwo() const
{
	return _exponent >= 0;
}

void Heightmap::Resize(int width, int height)
{

	_width = width;
	_height = height;

	_heightmap.resize(width);
	for (std::vector<float> & h : _heightmap) {
		h.resize(height);
	}

	CalculateExponent();
}

void Heightmap::Resize(int exponent)
{
	_exponent = exponent;
	_width = static_cast<int>(pow(2, exponent));
	_height = _width;
	Resize(_height, _width);
}

void Heightmap::Normalize()
{
	//TODO: problema, si normalizamos siempre, casi siempre va a haber un punto que valga 1.0f
	float min = _heightmap[0][0];
	float max = _heightmap[0][0];

	//bool need_normalize = false;

	//Get the max and the min values of the heightmap
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {

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
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {

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



	for (int j = 0; j < _height; j++) {
		for (int i = 0; i < _width; i++) {
			unsigned short int value(tools::FloatToShortInt(_heightmap[i][j]));
			rawFile.write(reinterpret_cast<const char*>(&value), sizeof(unsigned short int));
		}
	}


	rawFile.close();


}

inline TERRAINGENERATOR_API Heightmap operator+(const Heightmap & lhh, const Heightmap & rhh)
{

	if (lhh.GetWidth() != rhh.GetWidth() || lhh.GetHeight() != rhh.GetHeight()) {
		throw std::length_error{ "The heightmaps size are diferent" };
	}



	Heightmap heightmap_add(lhh.GetWidth(), lhh.GetHeight());
	for (int i = 0; i < lhh.GetWidth(); i++) {
		for (int j = 0; j < lhh.GetHeight(); j++) {
			heightmap_add[i][j] = lhh[i][j] + rhh[i][j];
		}
	}

	return heightmap_add;
}

inline TERRAINGENERATOR_API Heightmap operator-(const Heightmap & lhh, const Heightmap & rhh)
{
	if (lhh.GetWidth() != rhh.GetWidth() || lhh.GetHeight() != rhh.GetHeight()) {
		throw std::length_error{ "The heightmaps size are diferent" };
	}

	Heightmap heightmap_add(lhh.GetWidth(), lhh.GetHeight());
	for (int i = 0; i < lhh.GetWidth(); i++) {
		for (int j = 0; j < lhh.GetHeight(); j++) {
			heightmap_add[i][j] = lhh[i][j] - rhh[i][j];
		}
	}

	return heightmap_add;
}
