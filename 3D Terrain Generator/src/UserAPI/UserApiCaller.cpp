#include "UserApiCaller.h"
#include <algorithm>

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
float* _data;

float* GetData(int size, int* outValue){

	int halfSize = (std::pow(2, size)) + 1;
	int sizeHeightmap =  halfSize * halfSize;

	_data = new float[sizeHeightmap];
	
	user_api::Terrain terrain = user_api::GenerateTerrain(size, user_api::TerrainPreset::Hilly);
	
	//size del terrain es: terrain.size^2 + 1;

	for (int i = 0; i < halfSize; i++){
		for (int j = 0; j < halfSize; j++){
			
			_data[i + (j * halfSize)] = terrain.GetData()[i + j * halfSize];
		
		
		}	
	}
	*outValue = sizeof(float)* sizeHeightmap;
	

	return _data;


}

void DeleteData(){
	delete _data;
}
