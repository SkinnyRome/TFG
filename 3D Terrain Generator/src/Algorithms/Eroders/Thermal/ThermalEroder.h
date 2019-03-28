#ifndef THERMALERODER_H
#define THERMALERODER_H

#include <vector>
#include <utility>

#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

class Heightmap;

using Cell = std::pair<int, int>;


enum class ErosionType {THERMAL, HYDRAULIC};

struct TERRAINGENERATOR_API ErosionProperties {

	ErosionProperties() = delete;

	ErosionProperties(ErosionType t);
	
	ErosionType type;

	int number_of_iterations;
	
	struct {
		float talus_angle;
		float cFactor;
	} pThermal;

	struct { 
		
		int rain_constant;
		int evaporation_constant;
		int capacity_constant;
		int sediment_constant;
	
	
	} pHydraulic;
	

};


const std::vector<Cell> vNeighboursIndex{ { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };	//Von Neuman neigbours index.


bool IsInRange(const int& i, const int& j, const int &w, const int &h);


void TERRAINGENERATOR_API ErodeHeightmap(Heightmap& h, ErosionProperties pErosion);

void ThermalErosion(Heightmap& h, int nIterations, float tAngle, float cFactor);

void HydraulicErosion(Heightmap& h, int nIterations, float k1, float k2, float k3, float k4);


#endif //THERMALERODER_H