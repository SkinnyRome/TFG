#include <time.h>
#include <array>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <algorithm>
#include <limits>
#include <fstream> 
#include <vector>
#include <random>
#include <numeric>
#include "Heightmap\Heightmap.h"
#include "Algorithms\Perlin Noise\PerlinNoise.h"

using namespace std;

const int EXPONENT = 3;

const int SIZE = 9;

/*This bi-dimensional array is the data structure which stores the values of the heightmap. Those values are
in the interval of [0.0 - 1.0]*/



#pragma region MID POINT ALGORITHM	

//http://stevelosh.com/blog/2016/02/midpoint-displacement/

//Esta función pasa los valores en punto flotante de 32 bits a enteros de 16 bits
#define FloatToShortInt(f) ((f) >= 1.0 ? 65535 : (unsigned short int)((f)*65536.0))


/*

			COMO LA MATRIZ DEL HEIGHTMAP NO ESTÁ EN MEMORIA CONTINUA, HAY QUE BUSCAR UNA FORMA DE ESCRIBIRLO BIEN EN EL ARCHIVO, DE FORMA
			QUE SOLO SE ESCRIBAN LOS BYTES NECESARIOS Y NO MÁS DE LA CUENTA.

*/

/*

//This funciont returns random value [0.0, 1.0]
float GetNormalizedRandomValue() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

float GetRandomValueBetween(float a, float b) {

	return a + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (b - a)));

}

//Function to randomly move a point up or down
float Jitter(float value, float spread) {
	return value += GetRandomValueBetween(-spread, spread);
}

int Midpoint(int a, int b) {
	return (a + b) / 2;
}

float Average2(float a, float b) {
	return (a + b) / 2;
}

float Average4(float a, float b, float c, float d) {
	return (a + b + c + d) / 4;
}

//Main step of the algorithm
void MidPointDisplace(int lx, int rx, int ty, int by, float spread) {
	
	//Obtain the axis center points of the block
	int cx = Midpoint(lx, rx);
	int cy = Midpoint(ty, by);

	//Get the values of the corner of the block in the heightmap
	float top_left = _heightMap[ty][lx];
	float top_right = _heightMap[ty][rx];
	float bottom_left = _heightMap[lx][by];
	float bottom_right = _heightMap[rx][by];
	
	//Calculate the average and add them a random value
	float top = Average2(top_left, top_right);
	float left = Average2(top_left, bottom_left);
	float bottom = Average2(bottom_left, bottom_right);
	float right = Average2(top_right, bottom_right);
	float center = Average4(top, left, bottom, right);

	_heightMap[cx][by] = Jitter(bottom, spread);
	_heightMap[cx][ty] = Jitter(top, spread);
	_heightMap[lx][cy] = Jitter(left, spread);
	_heightMap[rx][cy] = Jitter(right, spread);
	_heightMap[cx][cy] = Jitter(center, spread);

}

//Algorithm function
void MidPointDisplacementAlgorithm() {

	//1. Initialize the corners of the heightmap with random values (between 0.0 and 1.0)
	_heightMap[0][0] = GetNormalizedRandomValue();					//Top-left corner
	_heightMap[SIZE - 1][0] = GetNormalizedRandomValue();			//Top-right corner
	_heightMap[0][SIZE - 1]  = GetNormalizedRandomValue();	//Bot-left corner
	_heightMap[SIZE -1][SIZE - 1] = GetNormalizedRandomValue();	//Top-left corner

	//Calculate the iterations needed to compute all the points (equal to exponent value)
	int iterations = EXPONENT;

	//Values used to randomize the variation added to a point
	float spread = 0.3f;
	float roughness = 0.5f;

	for (int i = 0; i < iterations; i++) {

		//Calculate the number of blocks in this iteration (2 pow i)
		int blocks = static_cast<int>(pow(2, i));

		//Calculate the width of each block
		int blockSize = (SIZE - 1) / blocks;

		//Get the corners of every block and call MidPointDisplace 
		for (int x = 0; x < blocks; x++) {
			for (int y = 0; y < blocks; y++) {

				int left_x = (blockSize * x);
				int right_x = (left_x + blockSize);
				int bottom_y = (blockSize * y);
				int top_y = (bottom_y + blockSize);

				MidPointDisplace(left_x, right_x, top_y, bottom_y, spread);

			}
		}

		//Reduce the spread value
		spread *= roughness;

	}

	//Normalize values of the heightmap so they are between [0.0, 1.0]

	

}


void SetRandomValues() {

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			_heightMap[i][j] = GetNormalizedRandomValue();
		}
	}

}

*/
#pragma endregion 


#pragma region CORTE
/*
struct Point {

	Point():x(0), y(0) {};

	Point(float x, float y): x(x), y(y){}

	Point(const Point& p) {
		x = p.x;
		y = p.y;
	}

	float operator*(const Point& p) {

		return (x * p.x) + (y * p.y);
	}

	Point operator*(const float t) {
		return Point(x*t, y*t);
	}

	Point operator/(const Point& p) {
		return Point(x / p.x, y / p.y);
	}

	Point operator-(const Point& p) {
		return Point(x - p.x, y - p.y);
	}

	Point operator+(const Point& p) {
		return Point(x + p.x, y + p.y);
	}

	float modulo() {

		float xPow = (float)pow(x, 2);
		float yPow = (float)pow(y, 2);
		return xPow + yPow;
	}

	float x;
	float y;

};
typedef std::pair<std::pair<Point, Point>, float> PuntosYValor;


Point ClosestPointOnSegment( Point a, Point b, Point p) {
	Point diff = p - a;
	Point dir = b - a;

	float t = (diff * dir) / (dir * dir);

	return a + (dir * t);
}

bool CheckAboveOrBelow(Point a, Point b, Point p) {

	float Vx = (float)(b.x - a.x);
	float Vy = (float)(b.y - a.y);


	float pending = (Vy / Vx);

	if (Vy == 0 || Vx == 0)
		pending = 0;


	float vectorY = (p.x * pending) + a.y;

	if (vectorY >= p.y)
		return false;
	else
		return true;

}

void DoCortes(const vector<PuntosYValor>& v) {

	float totalIterations = v.size() * SIZE * SIZE;
	long int it = 0;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			Point p(i, j);

			for (size_t pv = 0; pv < v.size(); pv++) {

				//CheckAboveOrBelow(v[pv].first.first, v[pv].first.second, p) ? _heightMap[i][j] += v[pv].second : _heightMap[i][j] += (- v[pv].second);

				(ClosestPointOnSegment(v[pv].first.first, v[pv].first.second, p).modulo() > p.modulo()) ? _heightMap[i][j] += v[pv].second : _heightMap[i][j] += (-v[pv].second);
				it += 1;
			}
			std::cout << ((it / totalIterations) * 100) << "%" <<  std::endl;
		}
	}




}

PuntosYValor RandomCut(int axis) {


	int x1, x2, y1, y2;

	
	//X Axis
	if (axis == 0) {

		x1 = 0;
		y1 = rand() % (SIZE - 1);


		x2 = SIZE - 1;
		y2 = rand() % (SIZE - 1);

	}
	//Y Axis
	else {

		x1 = rand() % (SIZE - 1);
		y1 = 0;

		x2 = rand() % (SIZE - 1);
		y2 = SIZE - 1;


	}

	float valor = GetRandomValueBetween(-0.5f, 0.5f);

	return PuntosYValor(std::pair<Point, Point>(Point(x1, y1), Point(x2, y2)), valor);

}

void AlgoritmoCorte() {

	const int nIterations = 10000;

	vector<PuntosYValor> puntosDeCorte;
	puntosDeCorte.reserve(nIterations);
	

	for (int i = 0; i < nIterations; i++) {

		puntosDeCorte.push_back(RandomCut(0));

	}


	DoCortes(puntosDeCorte);


}*/
#pragma endregion




#pragma region VORONOI DIAGRAM

/*
Point CreateRandomSite() {

	float x = GetRandomValueBetween(0, SIZE - 1);
	float y = GetRandomValueBetween(0, SIZE - 1);


	return Point(x, y);

}


void VoronoiDiagram() {


	const int nSites = 15;
	const float fallOff = 0.5f;
	const float dropOff = 0.3f;

	std::vector<std::pair<Point, float>> sites;

	for (int i = 0; i < nSites; i++) {
		float value = GetRandomValueBetween(0.8f, 1.0f);
		Point p = CreateRandomSite();
		sites.push_back(std::pair<Point,float>(p, value));

		_heightMap[(int)p.x][(int)p.y] = value;
	}


	float minDistance;
	float maxDistance = sqrt(pow((SIZE), 2) + pow((SIZE), 2));
	bool isSite;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {


			minDistance = SIZE * SIZE;
			isSite = false;
			std::pair<Point,float> nearestSite;
			float distance;
			int s = 0;
			while  (s < nSites && !isSite) {

				distance = sqrt(pow((sites[s].first.x - i),2)+ pow((sites[s].first.y - j),2)) / maxDistance;
				
				if (distance == 0.0f)
					isSite = true;

				if (!isSite && distance < minDistance) {
					minDistance = distance;
					nearestSite = sites[s];
				}
				
				s++;
			}


			if (!isSite) {
				//lineal
				float h = nearestSite.second - (minDistance * fallOff);
				//combined
				//h -= pow(minDistance, dropOff);

				_heightMap[i][j] = h;
 			}

		}
	}

	NormalizeHeightmap();



}
*/
#pragma endregion

void PrintHeightMap(const Heightmap& h) {

	if (SIZE > 9)
		std::cout << "El Heightmap es demasiado grande" << std::endl;
	else {

		std::cout << "Imprimiendo heightmap" << std::endl;

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				//std::cout << FloatToShortInt(_heightMap[i][j]) << " - ";
				std::cout << h[i][j] << " - ";

			}
			std::cout << std::endl;
		}
	}

}


int main() {

	srand(time(NULL));

	Heightmap _heightMap(SIZE, SIZE);
	PerlinNoise p;


	//MidPointDisplacementAlgorithm();
	//PerlinNoise();
	//AlgoritmoCorte();
	//VoronoiDiagram();
	//CreateRawFile((char*)"../HeightMaps/VoronoiDiagram/Heightmap.raw");
	p.GenerateHeightmap(_heightMap);
	_heightMap.DumpToFile("Prueba.raw");
	

	PrintHeightMap(_heightMap);

	_getch();

	return 0;
}