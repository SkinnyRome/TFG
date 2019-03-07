#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <vector>
#include <iostream>

using namespace std;
using Matrix = vector<vector<float>>;

class Heightmap
{
private:

	int _width;
	int _height;
	Matrix _heightmap;

public:

	Heightmap();
	Heightmap(int width, int height);
	//Heightmap(const Heightmap& h);

	inline vector<float>& operator[](size_t i) { return _heightmap[i]; }

	~Heightmap();

	inline int GetWidth() { return _width; }
	inline int GetHeight() { return _height; }

	void Normalize();
	
	
	


};

#endif