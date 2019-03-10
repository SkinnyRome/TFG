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
#include "Algorithms\MidPointDisplacement\MidPointDisplacement.h"
#include <Tools\TerrainGenerationTools.h>

using namespace std;

#pragma region MID POINT ALGORITHM	

//http://stevelosh.com/blog/2016/02/midpoint-displacement/




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

	if (h.GetWidth() > 9 || h.GetHeight() > 9)
		std::cout << "El Heightmap es demasiado grande" << std::endl;
	else {

		std::cout << "Imprimiendo heightmap" << std::endl;

		for (int i = 0; i < h.GetWidth(); i++) {
			for (int j = 0; j < h.GetHeight(); j++) {
				//std::cout << FloatToShortInt(_heightMap[i][j]) << " - ";
				std::cout << h[i][j] << " - ";

			}
			std::cout << std::endl;
		}
	}

}


int main() {


	srand(time(NULL));

	Heightmap h_mpd(3);
	MidPointDisplacement::MidPointProperties mdp_p(0.5f, 0.5f);
	MidPointDisplacement mpd(mdp_p);

	mpd.GenerateHeightmap(h_mpd);

	h_mpd.DumpToFile("PruebaMidPoint");

	PrintHeightMap(h_mpd);


	//_getch();



	/*------------------------------------------------------------------------------------------*/




	Heightmap h_pn(9 , 9);
	PerlinNoise::PNProperties perlin_pn(2500);
	PerlinNoise pn(perlin_pn);

	pn.GenerateHeightmap(h_pn);

	h_pn.DumpToFile("PruebaPerlin");

	PrintHeightMap(h_pn);

	//_getch();

	/*-----------------------------------------------------------------------------------------*/

	tools::MixHeightmaps(h_mpd, h_pn, 0.5f);

	PrintHeightMap(h_mpd);

	_getch();

	return 0;
}