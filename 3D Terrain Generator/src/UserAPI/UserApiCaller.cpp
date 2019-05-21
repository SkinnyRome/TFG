#include "UserApiCaller.h"


user_api::Terrain* CreateClassTerrain(int size, user_api::TerrainProperties* terrain_properties){
	
	return &user_api::GenerateTerrain(size, *(terrain_properties));

}

void CreateRaw(user_api::Terrain* pObject, string path){

	if (pObject != NULL){
		pObject->CreateRaw(path);
	}

}

user_api::TerrainPreset* CreatePreset(int type){

	return (user_api::TerrainPreset*)type;
}

float* GetData(int size){

	
	user_api::Terrain terrain = user_api::GenerateTerrain(size, user_api::TerrainPreset::Hilly);
	return terrain.GetData();

}
