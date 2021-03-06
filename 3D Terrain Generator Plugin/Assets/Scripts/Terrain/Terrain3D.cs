﻿using UnityEditor;
using UnityEngine;
using System;
using System.Collections.Generic;
using System.Linq;


[ExecuteInEditMode]
public class Terrain3D : MonoBehaviour
{

    public Terrain terrain;
    TerrainData _terraindata;
    TerrainGenerator3DPlugin plugin;

    public enum resolution { LOW = 0, MEDIUM = 1, HIGH = 2, ULTRA = 3}

    public resolution heightmapResolution;

    public bool applyWater = true;
    public Texture2D waterTexture = null;

    //TERRAIN-------
    public int terrainSize = 100;
    public int terrainHeight = 10;

    public enum Preset {Hilly, Soft }
    public Preset presetTerrain = 0;


    public enum BaseAlgorithm {Perlin, DiamondSquare};
    public enum ErosionLevel { None, Low, Mid, High };
   
    public BaseAlgorithm baseAlgorithm = BaseAlgorithm.Perlin;
    public int numberMountains = 2;
    public float randomFactor = 0.2f;
    public float hillyFactor = 0.4f;
    public float smoothFactor = 0.5f;
    //public float riverFactor = 0;
    public ErosionLevel erosionLevel = ErosionLevel.None;

   




    //SPLATMAPS ---------------------------------------------
    [System.Serializable]
    public class SplatHeights
    {

        public Texture2D texture = null;
        public float minHeight = 0.1f;
        public float maxHeight = 0.2f;
        public float minSlope = 0;
        public float maxSlope = 1.5f;
        public float randomizer = 0;
        public bool remove = false;

    }

    public class privateSplatHeights
    {
        public privateSplatHeights(float r)
        {
            if (r < 0)
            {
                r = 0;
            }
            //Debug.Log(r);
            splatOffset += (r * 0.001f);

            if (r >= 1)
                tileSize = new Vector2(50 + (r * 2), 50 + (r * 2));
            splatNoiseXScale -= r;
            splatNoiseYScale += (r / 2);
            // splatNoiseScaler = r;
        }
        public SplatHeights splatHeights = new SplatHeights();
        public Vector2 tileOffset = new Vector2(0, 0);
        public Vector2 tileSize = new Vector2(100, 100);
        public float splatOffset = 0.1f;
        public float splatNoiseXScale = 0.01f;
        public float splatNoiseYScale = 0.01f;
        public float splatNoiseScaler = 0.1f;


    }


    public List<SplatHeights> splatHeightsList = new List<SplatHeights>()
    {
        new SplatHeights()
    };


    public List<privateSplatHeights> privateSplatHeightsList = new List<privateSplatHeights>()
    {
        new privateSplatHeights(1)
    };

    public void CustomTextures()
    {
        UpdatePrivateList();
        ApplySplatMaps();
    }

    public void TropicalLandscape()
    {

        privateSplatHeightsList.Clear();

        privateSplatHeights pH1 = new privateSplatHeights(1);
        pH1.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Sand1");
        pH1.splatHeights.minHeight = 0.0f;
        pH1.splatHeights.maxHeight = 0.2f;
        pH1.splatHeights.minSlope = 0.0f;
        pH1.splatHeights.maxSlope = 5.0f;
        pH1.splatHeights.randomizer = 5.0f;
        privateSplatHeightsList.Add(pH1);

        privateSplatHeights pH2 = new privateSplatHeights(1);
        pH2.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Vegetation1");
        pH2.splatHeights.minHeight = 0.05f;
        pH2.splatHeights.maxHeight = 0.4f;
        pH2.splatHeights.minSlope = 0.0f;
        pH2.splatHeights.maxSlope = 100.0f;
        privateSplatHeightsList.Add(pH2);


        privateSplatHeights pH3 = new privateSplatHeights(1);
        pH3.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Grass1");
        pH3.splatHeights.minHeight = 0.3f;
        pH3.splatHeights.maxHeight = 1.0f;
        pH3.splatHeights.minSlope = 5.0f;
        pH3.splatHeights.maxSlope = 100.0f;
        privateSplatHeightsList.Add(pH3);


        privateSplatHeights pH4 = new privateSplatHeights(1);
        pH4.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Wetland1");
        pH4.splatHeights.minHeight = 0.6f;
        pH4.splatHeights.maxHeight = 1.0f;
        pH4.splatHeights.minSlope = 0.0f;
        pH4.splatHeights.maxSlope = 100.0f;
        pH4.splatHeights.randomizer = 2.0f;
        privateSplatHeightsList.Add(pH4);

        privateSplatHeights pH5 = new privateSplatHeights(1);
        pH5.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Vegetation2");
        pH5.splatHeights.minHeight = 0.3f;
        pH5.splatHeights.maxHeight = 1.0f;
        pH5.splatHeights.minSlope = 2.0f;
        pH5.splatHeights.maxSlope = 60.0f;
        privateSplatHeightsList.Add(pH5);

        ApplySplatMaps();

    }
    public void AridLandscape()
    {

        privateSplatHeightsList.Clear();

        privateSplatHeights pH1 = new privateSplatHeights(1);
        pH1.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Dirt3");
        pH1.splatHeights.minHeight = 0.0f;
        pH1.splatHeights.maxHeight = 0.1f;
        pH1.splatHeights.minSlope = 0.0f;
        pH1.splatHeights.maxSlope = 1.0f;
        privateSplatHeightsList.Add(pH1);

        privateSplatHeights pH2 = new privateSplatHeights(1);
        pH2.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Sand1");
        pH2.splatHeights.minHeight = 0.1f;
        pH2.splatHeights.maxHeight = 1.0f;
        pH2.splatHeights.minSlope = 0.0f;
        pH2.splatHeights.maxSlope = 50.0f;
        privateSplatHeightsList.Add(pH2);


        privateSplatHeights pH3 = new privateSplatHeights(1);
        pH3.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Rock16");
        pH3.splatHeights.minHeight = 0.1f;
        pH3.splatHeights.maxHeight = 1.0f;
        pH3.splatHeights.minSlope = 5.0f;
        pH3.splatHeights.maxSlope = 100.0f;
        privateSplatHeightsList.Add(pH3);


        privateSplatHeights pH4 = new privateSplatHeights(1);
        pH4.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Dirt1");
        pH4.splatHeights.minHeight = 0.0f;
        pH4.splatHeights.maxHeight = 0.2f;
        pH4.splatHeights.minSlope = 1.0f;
        pH4.splatHeights.maxSlope = 20.0f;
        privateSplatHeightsList.Add(pH4);

        privateSplatHeights pH5 = new privateSplatHeights(1);
        pH5.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Sand1");
        pH5.splatHeights.minHeight = 0.0f;
        pH5.splatHeights.maxHeight = 0.1f;
        pH5.splatHeights.minSlope = 0.0f;
        pH5.splatHeights.maxSlope = 1.5f;
        privateSplatHeightsList.Add(pH5);

        ApplySplatMaps();

    }

    public void SnowyLandscape()
    {

        privateSplatHeightsList.Clear();

        privateSplatHeights pH1 = new privateSplatHeights(1);
        pH1.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Rock2");
        pH1.splatHeights.minHeight = 0.0f;
        pH1.splatHeights.maxHeight = 1.0f;
        pH1.splatHeights.minSlope = 40.0f;
        pH1.splatHeights.maxSlope = 90.0f;
        privateSplatHeightsList.Add(pH1);

        privateSplatHeights pH2 = new privateSplatHeights(1);
        pH2.splatHeights.texture = (Texture2D)Resources.Load("TexturePack/Atex_Snow4");
        pH2.splatHeights.minHeight = 0.0f;
        pH2.splatHeights.maxHeight = 1.0f;
        pH2.splatHeights.minSlope = 0.0f;
        pH2.splatHeights.maxSlope = 55.0f;
        privateSplatHeightsList.Add(pH2);

        ApplySplatMaps();

    }

    public void AddNewSplatHeight()
    {
        splatHeightsList.Add(new SplatHeights());
    }

    public void RemoveSplatHeight()
    {
        List<SplatHeights> keptSplatHeights = new List<SplatHeights>();
        for (int i = 0; i < splatHeightsList.Count; i++)
        {
            if (!splatHeightsList[i].remove)
            {
                keptSplatHeights.Add(splatHeightsList[i]);
            }
        }
        if (keptSplatHeights.Count == 0) 
        {
            keptSplatHeights.Add(splatHeightsList[0]); 
        }
        splatHeightsList = keptSplatHeights;
    }

    void UpdatePrivateList()
    {

        privateSplatHeightsList.Clear();

        foreach (SplatHeights sH in splatHeightsList)
        {
            privateSplatHeights pH = new privateSplatHeights(sH.randomizer);
            pH.splatHeights = sH;
            Debug.Log(sH.texture);
            privateSplatHeightsList.Add(pH);

        }

        if (applyWater) {

            privateSplatHeights water = new privateSplatHeights(0);
            water.splatHeights.texture = waterTexture;
            water.splatHeights.minHeight = 0.0f;
            water.splatHeights.maxHeight = 0.0f;
            water.splatHeights.minSlope = 0.0f;
            water.splatHeights.maxSlope = 0.0f;
            privateSplatHeightsList.Add(water);

        }

    }

    float GetSteepness(float[,] heightmap, int x, int y, int width, int height)
    {
        float h = heightmap[x, y];
        int nx = x + 1;
        int ny = y + 1;

        if (nx > width - 1) nx = x - 1;
        if (ny > height - 1) ny = y - 1;

        float dx = heightmap[nx, y] - h;
        float dy = heightmap[x, ny] - h;
        Vector2 gradient = new Vector2(dx, dy);

        float steep = gradient.magnitude;

        return steep;
    }

    
    public void ApplySplatMaps()
    {

        SplatPrototype[] newSMPrototypes;
        newSMPrototypes = new SplatPrototype[privateSplatHeightsList.Count];
       
        for (int i = 0; i < privateSplatHeightsList.Count; i++)
        {

            newSMPrototypes[i] = new SplatPrototype();
            newSMPrototypes[i].texture = privateSplatHeightsList[i].splatHeights.texture;
            newSMPrototypes[i].tileOffset = privateSplatHeightsList[i].tileOffset;
            newSMPrototypes[i].tileSize = privateSplatHeightsList[i].tileSize;
            newSMPrototypes[i].texture.Apply(true);

        }

        _terraindata.splatPrototypes = newSMPrototypes;

        float[,] heightMap = _terraindata.GetHeights(0, 0, _terraindata.heightmapWidth, _terraindata.heightmapHeight);

        float[,,] smData = new float[_terraindata.alphamapWidth, _terraindata.alphamapHeight, _terraindata.alphamapLayers];

        for (int y = 0; y < _terraindata.alphamapHeight; y++) {
            for (int x = 0; x < _terraindata.alphamapWidth; x++) {

                float[] splat = new float[_terraindata.alphamapLayers];
                for (int i = 0; i < privateSplatHeightsList.Count; i++) {

                    float noise = Mathf.PerlinNoise(x * privateSplatHeightsList[i].splatNoiseXScale,
                                    y * privateSplatHeightsList[i].splatNoiseYScale) * privateSplatHeightsList[i].splatNoiseScaler;

                    float offset = privateSplatHeightsList[i].splatOffset + noise;
                    //offset = 0;
                    float heightLimitBot = privateSplatHeightsList[i].splatHeights.minHeight - offset;
                    float heightLimitTop = privateSplatHeightsList[i].splatHeights.maxHeight + offset;

                    //Debug.Log(heightLimitBot + "/" + heightLimitTop);

                    float hilly = _terraindata.GetSteepness(y / (float)_terraindata.alphamapHeight, x / (float)_terraindata.alphamapWidth);
                    //float hilly = GetSteepness(heightMap, x, y, _terraindata.heightmapWidth, _terraindata.heightmapHeight);
                    //Usamos la version de Unity por que esta mas optimizada y de cara al usuario es mas comoda de utilzar ya que el rango de inclinacion
                    //va de 0-90 y es mas intuitivo.


                    if ((heightMap[x, y] >= heightLimitBot && heightMap[x, y] <= heightLimitTop) &&
                        (hilly >= privateSplatHeightsList[i].splatHeights.minSlope && hilly <= privateSplatHeightsList[i].splatHeights.maxSlope))
                    {
                        splat[i] = 1;

                    }


                }
                NormalizeVector(splat);

                for (int j = 0; j < privateSplatHeightsList.Count; j++) {
                    smData[x, y, j] = splat[j];
                
                }


            }

        }

        _terraindata.SetAlphamaps(0, 0, smData);



    }



    void NormalizeVector(float[] v)
    {
        float total = 0;
        for (int i = 0; i < v.Length; i++)
        {
            total += v[i];
        }

        for (int i = 0; i < v.Length; i++)
        {
            v[i] /= total;
        }
    }

    public void CreatePresetTerrain() {
        
        
        Vector3 pos = new Vector3(0, 0, 0);
       
        GameObject t = null;
        _terraindata = new TerrainData();
        t = Terrain.CreateTerrainGameObject(_terraindata);
        t.transform.parent = this.transform;

        int realSize = 5 + (int)heightmapResolution;
        _terraindata.heightmapResolution = (int)(Mathf.Pow(2.0f, realSize) + 1.0f);


        _terraindata.baseMapResolution = terrainSize;

        _terraindata.SetDetailResolution(terrainSize, 16);


        _terraindata.size = new Vector3(terrainSize, terrainHeight, terrainSize);
        _terraindata.alphamapResolution = _terraindata.heightmapResolution;
        

        //Debug.Log("SIZE HEIGHTMAP TERRAIN: " + _terraindata.heightmapWidth + " -- " + _terraindata.heightmapHeight);
        //Debug.Log(_terraindata.size);

        plugin = this.GetComponent<TerrainGenerator3DPlugin>();
        //Debug.Log("REAL SIZE: " + realSize);
        
        plugin.CreatePresetTerrain((int)presetTerrain, realSize);

       
        float[,] n = plugin.GetHeights();
        _terraindata.SetHeights(0, 0, n);

    }



    public void CreateCustomTerrain() {

        Vector3 pos = new Vector3(0, 0, 0);
     
        GameObject t = null;
        _terraindata = new TerrainData();
        t = Terrain.CreateTerrainGameObject(_terraindata);
        t.transform.parent = this.transform;

        int realSize = 5 + (int)heightmapResolution;
        _terraindata.heightmapResolution = (int)(Mathf.Pow(2.0f, realSize) + 1.0f);


        _terraindata.baseMapResolution = terrainSize;

        _terraindata.SetDetailResolution(terrainSize, 16);


        _terraindata.size = new Vector3(terrainSize, terrainHeight, terrainSize);
        _terraindata.alphamapResolution = _terraindata.heightmapResolution;

        //Debug.Log("SIZE SPLATMAP: " + _terraindata.alphamapWidth + "--" + _terraindata.alphamapHeight);
       
        //Debug.Log("SIZE HEIGHTMAP TERRAIN: " + _terraindata.heightmapWidth + " -- " + _terraindata.heightmapHeight);
        //Debug.Log(_terraindata.size);

        plugin = this.GetComponent<TerrainGenerator3DPlugin>();
        //Debug.Log("REAL SIZE: " + realSize);
  
        plugin.CreateBasicTerrain((int)baseAlgorithm, numberMountains,  randomFactor, hillyFactor,  smoothFactor,  (int)erosionLevel, realSize);

        float[,] n = plugin.GetHeights();
        _terraindata.SetHeights(0, 0, n);        

    }


    void OnEnable()
    {
        Debug.Log("Initialising Terrain Data");        
    }

}
