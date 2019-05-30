using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

public class TerrainGenerator3DPlugin : MonoBehaviour
{
    private System.IntPtr _nativePreset;

    private float[,] realArr;
    private float[,] trasposeArr;
    private System.Single[] auxArr;
    private System.IntPtr pointer;
    private int size;
    //Metodos publicos para el usuario de Unity
    public void createBasicTerrain(int s)
    {

        Debug.Log("Creating Terrain");
        //_nativePreset = CreatePreset(1);

        //_nativeTerrain = GenerateTerrain(512, _nativePreset);

        //_nativeTerrain = CreateClassTerrain(512, _nativePreset);
        size = s;
        pointer = System.IntPtr.Zero;

       
        int tam = 0;

        pointer = GetData(size * size, out tam);        

        Debug.Log("SIZE C++ bytes: " + tam);
        
        Debug.Log("SIZE C#: " + size * size);
        Debug.Log(pointer);
        realArr = new float[s, s];
        auxArr = new float[s * s];
        byte[] by = new byte[tam];
        trasposeArr = new float[s, s];
        size = s;

        //Marshal.Copy(pointer,auxArr,0,tam);
        Marshal.Copy(pointer,by,0,tam);
        Debug.Log("Marshal completed");

      

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {

                auxArr[i + j * size]  = System.BitConverter.ToSingle(by, (i + j * size) * sizeof(float));
                //Debug.Log(i+ "-" + j + ": " + auxArr[i + j * size]);
                realArr[i, j] = auxArr[i + j * size];
                trasposeArr[j, i] = realArr[i, j];
            }
            //Debug.Log("----");
        }



        Debug.Log("Size array: " + realArr.Length);
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                Debug.Log(realArr[i, j]);
            }
        }


        

        
        Debug.Log("Terrain finished");



    }

    /*public unsafe void getArray(float[] array, int s) {

        fixed (float* p = array){
            GetData((System.IntPtr)s, (System.IntPtr)p);
        }
    }*/


    public float[,] GetHeights()
    {
        return trasposeArr;
    }
    public int GetSize()
    {
        return size;
    }


    void Start()
    {
        //createBasicTerrain(8);

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

    [DllImport("3D Terrain Generator")]
    private static extern System.IntPtr GetData(int size, out int outValue);

    //float* GetData(int size, int* outValue){


}
