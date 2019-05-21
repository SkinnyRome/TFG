using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class TerrainGenerator3DPlugin : MonoBehaviour
{



    private System.IntPtr _nativePreset;

    private float[,] realArr;
    private System.Single[] auxArr;
    private int size;
    //Metodos publicos para el usuario de Unity
    public void createBasicTerrain(int s)
    {

        Debug.Log("Creating Terrain");
        //_nativePreset = CreatePreset(1);

        //_nativeTerrain = GenerateTerrain(512, _nativePreset);

        //_nativeTerrain = CreateClassTerrain(512, _nativePreset);
        size = s;

        System.IntPtr arr;


        arr = GetData((System.IntPtr)size);

        Debug.Log(s);
        Debug.Log(arr);
        realArr = new float[s, s];
        auxArr = new float[s * s];
        size = s;

        Marshal.Copy(arr, auxArr, 0, s * s);

        Debug.Log("Size array: " + auxArr.Length);
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                realArr[j, i] = auxArr[i + (j * s)];
            }
        }

        Debug.Log("Terrain finished");



    }

    public float[,] GetHeights()
    {
        return realArr;
    }
    public int GetSize()
    {
        return size;
    }


    void Start()
    {
        createBasicTerrain(8);

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

    [DllImport("3D Terrain Generator_d")]
    private static extern System.IntPtr GetData(System.IntPtr size);



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
