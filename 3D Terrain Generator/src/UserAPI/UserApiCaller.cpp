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
float* _data;

float* GetData(int size, int* outValue){

	_data = new float [size * size];
	
	user_api::Terrain terrain = user_api::GenerateTerrain(size, user_api::TerrainPreset::Hilly);
	

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			
			_data[i + (j * size)] = terrain.GetData()[i + j * size];;
		
		
		}	
	}
	*outValue = sizeof(float) * size * size;
	

	return _data;


}

void DeleteData(){
	delete _data;
}
