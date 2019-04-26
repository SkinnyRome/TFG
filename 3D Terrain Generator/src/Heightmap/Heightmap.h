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
	int _size;
	vector<vector<float>> _heightmap;

	void SetSizeAndExp();

public:

	Heightmap(int size = 3);
	//Heightmap(const Heightmap& h);

	const vector<float>& operator[](int i) const { return _heightmap[i]; }
	vector<float>& operator[](int i)  { return _heightmap[i]; }
	inline Heightmap operator+(const float a);
	inline Heightmap operator*(const float a);
	

	void Resize(int width, int height);
	void Resize(int exponent);

	int GetSize() const { return _size; }
	int GetExponent() const { return _exponent; }

	void SetExponent(int exponent) { _exponent = exponent; }

	void Normalize();
	void DumpToFile(string filename, RawMode mode = B_16);
	
	
};

inline TERRAINGENERATOR_API Heightmap operator+(const Heightmap& lhh, const Heightmap& rhh);
inline TERRAINGENERATOR_API Heightmap operator-(const Heightmap& lhh, const Heightmap& rhh);

#endif