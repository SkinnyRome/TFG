#ifndef USERAPICALLER_H
#define USERAPICALLER_H

#ifdef TERRAINGENERATOR_EXPORTS
#define TERRAINGENERATOR_API __declspec(dllexport)
#else
#define TERRAINGENERATOR_API __declspec(dllimport)
#endif

#include "UserAPI.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern TERRAINGENERATOR_API user_api::Terrain* CreateClassTerrain(int size, user_api::TerrainProperties* terrain_properties);

	extern TERRAINGENERATOR_API void CreateRaw(user_api::Terrain* pObject, string path);

	//Presets
	extern TERRAINGENERATOR_API user_api::TerrainPreset* CreatePreset(int type);

	
	extern TERRAINGENERATOR_API float* GetData(user_api::BaseAlgorithm base, int numberMountains, float randomFactor, float hillyFactor, float smoothFactor, user_api::ErosionLevel erosion, int size, int* outValue);

	/*   public BaseAlgorithm baseAlgorithm = BaseAlgorithm.Perlin;
    public int numberMountains = 2;
    public float randomFactor = 0.2f;
    public float hillyFactor = 0.4f;
    public float smoothFactor = 0.5f;
    //public float riverFactor = 0;
    public ErosionLevel erosionLevel = ErosionLevel.None;*/
	
	extern TERRAINGENERATOR_API void DeleteData();
	



#ifdef __cplusplus
}
#endif




#endif