#ifndef THERMALERODER_H
#define THERMALERODER_H


#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif


enum class ErosionType {THERMAL, AQUA};

struct TERRAINGENERATOR_API ThermalErosionProp {

	ThermalErosionProp() :nIterations(50), tAngle(4.0f), cFactor(0.5f) {}

	int nIterations;
	float tAngle;
	float cFactor;
};

struct TERRAINGENERATOR_API AquaErosionProp {

};

struct TERRAINGENERATOR_API ErosionProperties {

	ErosionProperties() = delete;

	ErosionProperties(ErosionType t);
	
	ErosionType type;

	union {
		struct {
			int nIterations;
			float tAngle;
			float cFactor;
		} pThermal;
		struct { int a; } pAqua;
	};

};


class Heightmap;


bool IsInRange(const int& i, const int& j, const int &w, const int &h);


void TERRAINGENERATOR_API ErodeHeightmap(Heightmap& h, ErosionProperties pErosion);

void ThermalErosion(Heightmap& h, int nIterations, float tAngle, float cFactor);


#endif //THERMALERODER_H