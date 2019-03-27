using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class TerrainGenerator3DPlugin : MonoBehaviour{


    //private IntPtr _nativeHeightmap = IntPtr.Zero;

    //Metodos publicos para el usuario de Unity
    public void createBasicTerrain() {
        //Podriamos llamar a la api 
        float f = GetRandomValueBetween(1, 12);
        Debug.Log("heeey" + f);

        float j = Average2(1, 2);
        Debug.Log("MEDIA" + j);


    }


    void Start() {
        createBasicTerrain();
        
    }



    //-------------------------------------------------------------------
    //Metodos privados para llamar al plugin
    [DllImport ("3D Terrain Generator_d")]
    private static extern float GetRandomValueBetween(float a, float b);

    [DllImport("3D Terrain Generator_d")]
    private static extern float Average2(float a, float b);

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
