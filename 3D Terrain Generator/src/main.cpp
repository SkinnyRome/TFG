#include <time.h>
#include <array>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <algorithm>
#include <limits>

using namespace std;

//http://stevelosh.com/blog/2016/02/midpoint-displacement/




#define EXPONENT 5

const int SIZE = 33;

/*This bi-dimensional array is the data structure which stores the values of the heightmap. Those values are
in the interval of [0.0 - 1.0]*/
float _heightMap[SIZE][SIZE] = {0.0f}; 



void NormalizeHeightmap() {

	float min = _heightMap[0][0];
	float max = _heightMap[0][0];


	//Get the max and the min values of the heightmap
	for (int i = 0; i < SIZE - 1; i++) {
		for (int j = 0; j < SIZE - 1; j++) {

			float value = _heightMap[i][j];

			if (value > max)
				max = value;
			else if (value < min) {
				min = value;
			}
		}
	}

	//Normalize
	for (int i = 0; i < SIZE - 1; i++) {
		for (int j = 0; j < SIZE - 1; j++) {

			float value = _heightMap[i][j];

			_heightMap[i][j] = (value - min) / (max - min);

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

void PrintHeightMap() {

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			std::cout << _heightMap[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

int main() {

	srand(time(NULL));

	MidPointDisplacementAlgorithm();
	PrintHeightMap();

	_getch();

	return 0;
}