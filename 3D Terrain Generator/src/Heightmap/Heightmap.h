#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include <vector>
#include <iostream>
#include <stdexcept>


using std::vector;
using std::string;

enum RawMode {B_16, B_32};

class TERRAINGENERATOR_API Heightmap
{
private:

	int _exponent;
	int _width;
	int _height;
	vector<vector<float>> _heightmap;

public:

	Heightmap();
	Heightmap(int exponent);
	Heightmap(int width, int height);
	//Heightmap(const Heightmap& h);

	~Heightmap();

	const vector<float>& operator[](int i) const { return _heightmap[i]; }
	vector<float>& operator[](int i)  { return _heightmap[i]; }
	inline Heightmap operator+(const float a);
	inline Heightmap operator*(const float a);
	

	bool IsSquare() const;

	void Resize(int width, int height);
	void Resize(int exponent);

	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
	int GetExponent() const { return _exponent; }

	void SetExponent(int exponent) { _exponent = exponent; }

	void Normalize();
	void DumpToFile(string filename, RawMode mode = B_16);
	
	
};

inline TERRAINGENERATOR_API Heightmap operator+(const Heightmap& lhh, const Heightmap& rhh);
inline TERRAINGENERATOR_API Heightmap operator-(const Heightmap& lhh, const Heightmap& rhh);

#endif