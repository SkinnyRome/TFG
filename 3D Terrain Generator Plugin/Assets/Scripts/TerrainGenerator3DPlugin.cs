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
    public void createBasicTerrain(int baseAlg, int mountains, float randomFactor, float hillyFactor, float smoothFactor, int erosion, int s)
    {

        Debug.Log("Creating Terrain");
        //_nativePreset = CreatePreset(1);

        //_nativeTerrain = GenerateTerrain(512, _nativePreset);

        //_nativeTerrain = CreateClassTerrain(512, _nativePreset);
        size = s;
        int halfSize = (int)Mathf.Pow(2.0f, size)  + 1;

        pointer = System.IntPtr.Zero;

       
        int tam = 0;

        pointer = GetData( baseAlg,  mountains,  randomFactor,  hillyFactor,  smoothFactor,  erosion,  size, out tam);        

        Debug.Log("SIZE C++ bytes: " + tam);
        
        Debug.Log("SIZE C#: " + halfSize + "--" + halfSize);
        Debug.Log(pointer);
        realArr = new float[halfSize, halfSize];
        auxArr = new float[halfSize * halfSize];
        byte[] by = new byte[tam];
        trasposeArr = new float[halfSize, halfSize];
        

        //Marshal.Copy(pointer,auxArr,0,tam);
        Marshal.Copy(pointer,by,0,tam);
        Debug.Log("Marshal completed");

      

        for (int i = 0; i < halfSize; i++) {
            for (int j = 0; j < halfSize; j++) {

                auxArr[i + j * halfSize]  = System.BitConverter.ToSingle(by, (i + j * halfSize) * sizeof(float));
                //Debug.Log(i+ "-" + j + ": " + auxArr[i + j * size]);
                realArr[i, j] = auxArr[i + j * halfSize];
                trasposeArr[j, i] = realArr[i, j];
            }
            //Debug.Log("----");
        }



        Debug.Log("Size array: " + realArr.Length);


        

        
        Debug.Log("Terrain finished");



    }




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
 

       [DllImport("3D Terrain Generator")]
    private static extern System.IntPtr GetData(int baseAlg, int mountains, float randomFactor, float hillyFactor, float smoothFactor, int erosion, int size, out int outValue);

    //float* GetData(int size, int* outValue){


}
