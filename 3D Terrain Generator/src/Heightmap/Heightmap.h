#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <vector>
#include <iostream>


using namespace std;
enum RawMode {B_16, B_32};


class Heightmap
{
private:

	int _width;
	int _height;
	vector<vector<float>> _heightmap;

public:

	Heightmap();
	Heightmap(int width, int height);
	//Heightmap(const Heightmap& h);

	const vector<float>& operator[](int i) const { return _heightmap[i]; }
	vector<float>& operator[](int i)  { return _heightmap[i]; }

	

	~Heightmap();

	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

	void Normalize();
	void DumpToFile(string filename, RawMode mode = B_16) const;
	
};

#endif