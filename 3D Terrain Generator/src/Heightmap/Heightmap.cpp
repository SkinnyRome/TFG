#include "Heightmap.h"
#include <fstream>

#define FloatToShortInt(f) ((f) >= 1.0 ? 65535 : (unsigned short int)((f)*65536.0)) //TODO MOVE THIS


Heightmap::Heightmap():_width(), _height(), _heightmap()
{


}

Heightmap::Heightmap(int width, int height): _width(width), _height(height), _heightmap(_width, vector<float>(_height))
{


}


Heightmap::~Heightmap()
{
}

void Heightmap::Normalize()
{
	float min = _heightmap[0][0];
	float max = _heightmap[0][0];


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
	cout << "Max " << max << " Min " << min << endl;
#endif

	//Normalize
	for (int i = 0; i < _width; i++) {
		for (int j = 0; j < _height; j++) {

			float value = _heightmap[i][j];

			_heightmap[i][j] = (value - min) / (max - min);

		}
	}
}

void Heightmap::DumpToFile(string filename, RawMode mode) const
{

	string filepath("../HeightMaps/" + filename);


	std::ofstream rawFile;
	rawFile.open(filepath, std::fstream::binary | std::fstream::out);

	if (!rawFile.is_open())
		std::cout << "No se ha podido crear el archivo" << std::endl;



	for (int j = 0; j < _height; j++) {
		for (int i = 0; i < _width; i++) {
			unsigned short int value(FloatToShortInt(_heightmap[i][j]));
			rawFile.write(reinterpret_cast<const char*>(&value), sizeof(unsigned short int));
		}
	}


	rawFile.close();


}
