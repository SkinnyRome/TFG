#include <time.h>
#include <array>
#include <iostream>
#include <conio.h>

#define SIZE 3




//http://stevelosh.com/blog/2016/02/midpoint-displacement/



/*This bi-dimensional array is the data structure which stores the values of the heightmap. Those values are
in the interval of [0.0 - 1.0]*/
float _heightMap[SIZE][SIZE] = {0.0f}; 

//This funciont returns random value [0.0, 1.0]
float GetRandomValue() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

//Function to randomly move a point up or down
float Jitter(float value) {
	return value += GetRandomValue();
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
	
	int cx = Midpoint(lx, rx);
	int cy = Midpoint(ty, by);


	float top_left = _heightMap[ty][lx];
	float top_right = _heightMap[ty][rx];
	float bottom_left = _heightMap[lx][by];
	float bottom_right = _heightMap[rx][by];
	
	float top = Average2(top_left, top_right);
	float left = Average2(top_left, bottom_left);
	float bottom = Average2(bottom_left, bottom_right);
	float right = Average2(top_right, bottom_right);
	float center = Average4(top, left, bottom, right);


	_heightMap[cx][by] = Jitter(bottom);
	_heightMap[cx][ty] = Jitter(top);
	_heightMap[lx][cy] = Jitter(left);
	_heightMap[rx][cy] = Jitter(right);
	_heightMap[cx][cy] = Jitter(center);


	
}

//Algorithm function
void MidPointDisplacementAlgorithm() {

	//1. Initialize the corners of the heightmap with random values (between 0.0 and 1.0)
	_heightMap[0][0] = GetRandomValue();					//Top-left corner
	_heightMap[SIZE - 1][0] = GetRandomValue();			//Top-right corner
	_heightMap[0][SIZE - 1]  = GetRandomValue();	//Bot-left corner
	_heightMap[SIZE -1][SIZE - 1] = GetRandomValue();	//Top-left corner

	MidPointDisplace(0, SIZE - 1, 0, SIZE - 1, 0.3f);


}


void SetRandomValues() {

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			_heightMap[i][j] = GetRandomValue();
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