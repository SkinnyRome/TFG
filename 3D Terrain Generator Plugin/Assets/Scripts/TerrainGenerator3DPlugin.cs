using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class TerrainGenerator3DPlugin : MonoBehaviour
{


    private System.IntPtr _nativeTerrain;
    private System.IntPtr _nativePreset;


    //Metodos publicos para el usuario de Unity
    public void createBasicTerrain()
    {

        Debug.Log("Ejecutando");
        _nativePreset = CreatePreset(1);

        //_nativeTerrain = GenerateTerrain(512, _nativePreset);

        _nativeTerrain = CreateClassTerrain(512, _nativePreset);

        
        Debug.Log("heeey" + _nativePreset);

        Debug.Log("->>>>>>>>>>>>" + _nativeTerrain);



    }


    void Start()
    {
        createBasicTerrain();

    }



    //-------------------------------------------------------------------
    //Metodos privados para llamar al plugin
    [DllImport("3D Terrain Generator_d")]
    private static extern System.IntPtr CreateClassTerrain(int size, System.IntPtr terrain_properties);

    [DllImport("3D Terrain Generator_d")]
    private static extern void CreateRaw(System.IntPtr pTerrainObject, string path);


    [DllImport("3D Terrain Generator_d")]
    private static extern System.IntPtr CreatePreset(int type);


    [DllImport("3D Terrain Generator_d")]
    private static extern System.IntPtr GenerateTerrain(int size, System.IntPtr terrain_properties);



    /*Necesitamos crear un wrapper para poder usar los objetos.
     * En la lib c++ en las funciones que queramos usar en unity hay que poner
     * extern "C" __declspec(dllexport) nombreFun
     * 
     * y aqui podemos usarla con lo de arriba.
     * 
     * Para objetos habra que manejarlos aqui y pasarlos como parametro
     * 
             C++
         extern "C" {
             YourNativeObject* Internal_CreateNativeObject()
            {
                YourNativeObject* obj = new YourNativeObject();
                // you might want to store the object reference on the native side for tracking
                return obj;
            }
            void Internal_DestroyNativeObject(YourNativeObject* obj)
            {
                // may need to update your tracking in native code
                delete obj;
            }
            void Internal_SomeNativeMethod(YourNativeObject* obj, int SomeParameter)
            {
                obj->SomeNativeMethod(SomeParameter);
            }
        }

        *
        
         
        */

    //void 




}
