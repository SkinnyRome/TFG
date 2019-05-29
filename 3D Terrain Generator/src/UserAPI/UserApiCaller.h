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

	
	extern TERRAINGENERATOR_API float* GetData(int size );

	extern TERRAINGENERATOR_API void DeleteData();
	



#ifdef __cplusplus
}
#endif




#endif