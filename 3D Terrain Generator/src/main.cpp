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


using namespace std;

const int EXPONENT = 3;

const int SIZE = 256;

/*This bi-dimensional array is the data structure which stores the values of the heightmap. Those values are
in the interval of [0.0 - 1.0]*/
float _heightMap[SIZE][SIZE] = {0.0f}; 


#pragma region PERLIN NOISE ALGORITHM

//https://mzucker.github.io/html/perlin-noise-math-faq.html

//http://www.huttar.net/lars-kathy/graphics/perlin-noise/perlin-noise.html

//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/

//https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2


const int GRID_SIZE = 17;

std::vector<int> p;




float fade(float t) {

	return t * t * t * (t *(t * 6 - 15) + 10);


}

float lerp(float a, float b, float t) {
	return a + t * (b - a);
}


//Calculates a dot product between the vector x, y and a pseudo random gradient vector.
float grad(int hash, float x, float y) {

	return ((hash & 1) ? x : -x) + ((hash & 2) ? y : -y);

}

float noise(float x, float y) {

	//Find the pixel cell
	int cellX = (int)floor(x) & /*(GRID_SIZE - 1)*/ 255;
	int cellY = (int)floor(y) & /*(GRID_SIZE - 1)*/ 255;

	int cellX1 = (cellX + 1) & 255;
	int cellY1 = (cellY + 1) & 255;


	//Find the relative x, y of point in cube
	x -= floor(x);
	y -= floor(y);

	float u = fade(x);
	float v = fade(y);

	//Hash coordinates for the four corners of our grid cell (p[p[x] + y])
	int left_top_corner = p[p[cellX] + cellY];
	int right_top_corner = p[p[cellX1] + cellY];
	int left_bot_corner = p[p[cellX] + cellY1];
	int right_bot_corner = p[p[cellX1] + cellY1];

	//Obtain the dot products between the random gradients and the vectors pointing to P (x,y)
	float left_top_grad = grad(left_top_corner, x, y);
	float right_top_grad = grad(right_top_corner, x - 1, y);
	float left_bot_grad = grad(left_bot_corner, x, y - 1);
	float right_bot_grad = grad(right_bot_corner, x - 1, y - 1);

	//Interpolate
	float x1 = lerp(left_top_grad, right_top_grad, u);
	float x2 = lerp(left_bot_grad, right_bot_grad,  u);
	float r = lerp(x1, x2, v);

	return (r + 1.0f) / 2.0f;
}




void PerlinNoise() {

	//Create and initialize random vector values
	p.resize(256);
	iota(p.begin(), p.end(), 0);

	random_device rd;
	mt19937 g(rd());

	shuffle(p.begin(), p.end(), g);

	// Duplicate the permutation vector
	p.insert(p.end(), p.begin(), p.end());


	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			float x = (float)i / ((float) SIZE);
			float y = (float)j / ((float)SIZE);

			//Typical
			
			float n = noise(10 *x, 10 *y);

			//Wood
			//float n = 20 * noise(x,y);
			//n = n - floor(n);

			_heightMap[i][j] = n;


		}
	}



}






#pragma endregion


#pragma region MID POINT ALGORITHM	
//http://stevelosh.com/blog/2016/02/midpoint-displacement/

//Esta función pasa los valores en punto flotante de 32 bits a enteros de 16 bits
#define FloatToShortInt(f) ((f) >= 1.0 ? 65535 : (unsigned short int)((f)*65536.0))


/*

			COMO LA MATRIZ DEL HEIGHTMAP NO ESTÁ EN MEMORIA CONTINUA, HAY QUE BUSCAR UNA FORMA DE ESCRIBIRLO BIEN EN EL ARCHIVO, DE FORMA
			QUE SOLO SE ESCRIBAN LOS BYTES NECESARIOS Y NO MÁS DE LA CUENTA.

*/





void NormalizeHeightmap() {

	float min = _heightMap[0][0];
	float max = _heightMap[0][0];


	//Get the max and the min values of the heightmap
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {

			float value = _heightMap[i][j];

			if (value > max) {
				max = value;
			}
			if (value < min) {
				min = value;
			}
		}

	}
		std::cout << "Max " << max << " Min " << min << std::endl;

	//Normalize
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {

			float value = _heightMap[i][j];

			_heightMap[i][j] = (value - min) / (max - min);

			if (_heightMap[i][j] > 1 || _heightMap[i][j] < 0)
				std::cout << "Aqui hay un valor incorrecto " << _heightMap[i][j] << std::endl;
		}
	}

}

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
	NormalizeHeightmap();

	

}


void SetRandomValues() {

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			_heightMap[i][j] = GetNormalizedRandomValue();
		}
	}

}


#pragma endregion 

#pragma region CORTE

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

	NormalizeHeightmap();

}





#pragma endregion

void PrintHeightMap() {

	if (SIZE > 9)
		std::cout << "El Heightmap es demasiado grande" << std::endl;
	else {

		std::cout << "Imprimiendo heightmap" << std::endl;

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				std::cout << FloatToShortInt(_heightMap[i][j]) << " - ";
			}
			std::cout << std::endl;
		}
	}

}

void CreateRawFile(char* fileName) {


	/*		USING FILE
		FILE* rawFile;
		errno_t error;
		if ((error = fopen_s(&rawFile, fileName, "w")) != 0) {
			std::cout << "Error while opening/creating the file" << std::endl;
		}

		size_t writenElements = fwrite(_heightMap, sizeof(float), SIZE * SIZE, rawFile);
		
	
		if (writenElements < SIZE * SIZE) {
			std::cout << "Error while writing the file" << std::endl;
		}

		std::cout << "Se han escrito " << writenElements << " elementos" << std::endl;

		fclose(rawFile);
	
	*/
	

	/* USING OFSTREAM */



	std::ofstream rawFile;
	rawFile.open(fileName, std::fstream::binary | std::fstream::out);

	if (!rawFile.is_open())
		std::cout << "No se ha podido crear el archivo" << std::endl;

	for (int j = 0; j < SIZE; j++) {
		for (int i = 0; i < SIZE; i++) {
			unsigned short int* value = new unsigned short int(FloatToShortInt(_heightMap[i][j]));
			rawFile.write(reinterpret_cast<const char*>(value), sizeof(unsigned short int));
		}
	}


	rawFile.close();

}






int main() {

	srand(time(NULL));



	//MidPointDisplacementAlgorithm();
	//PerlinNoise();
	AlgoritmoCorte();
	CreateRawFile((char*)"../HeightMaps/CutAlgorithm/Heightmap.raw");

	PrintHeightMap();

	_getch();

	return 0;
}