using UnityEditor;
using UnityEngine;
using EditorGUITable;

[CustomEditor(typeof(Terrain3D))]
public class Terrain3DEditor : Editor
{
    GUITableState splatMapTable;
    SerializedProperty SplatHeights;

    SerializedProperty baseAlgorithm;
    SerializedProperty numberMountains;
    SerializedProperty randomFactor;
    SerializedProperty hillyFactor;
    SerializedProperty smoothFactor;
    SerializedProperty erosionLevel;

    SerializedProperty waterTexture;
    SerializedProperty seaLevel;
    SerializedProperty applyWater;

    SerializedProperty terrainSize;
    SerializedProperty terrainHeight;
    SerializedProperty heightmapResolution;

    SerializedProperty presetTerrain;



    Vector2 scrollPos;

    bool showWaterConfig = false;

    bool showCreateTerrain = false;
    bool showPresets = false;  
    bool showCustomCreateTerrain = false;


    bool showDrawTerrain = false;
    bool showCustomDrawingData = false;
    bool showSnowy = false;
    bool showTropical = false;
    bool showArid = false;

    void OnEnable()
    {

        splatMapTable = new GUITableState("splatMapTable");
        
        SplatHeights = serializedObject.FindProperty("SplatHeights");
        waterTexture = serializedObject.FindProperty("waterTexture");
        seaLevel = serializedObject.FindProperty("seaLevel");
        applyWater = serializedObject.FindProperty("applyWater");
        terrainSize = serializedObject.FindProperty("terrainSize");
        terrainHeight = serializedObject.FindProperty("terrainHeight");
        heightmapResolution = serializedObject.FindProperty("heightmapResolution");

        baseAlgorithm = serializedObject.FindProperty("baseAlgorithm");
        numberMountains = serializedObject.FindProperty("numberMountains");
        randomFactor = serializedObject.FindProperty("randomFactor");
        hillyFactor = serializedObject.FindProperty("hillyFactor");
        smoothFactor = serializedObject.FindProperty("smoothFactor");
        erosionLevel = serializedObject.FindProperty("erosionLevel");

        presetTerrain = serializedObject.FindProperty("presetTerrain");

    }


    public override void OnInspectorGUI()
    {

        serializedObject.Update();

        Terrain3D terrain = (Terrain3D)target;
        
        Rect r = EditorGUILayout.BeginVertical();
        scrollPos = EditorGUILayout.BeginScrollView(scrollPos, GUILayout.Width(r.width), GUILayout.Height(r.height));
        EditorGUI.indentLevel++;

        GUILayout.Label("Terrain Generation", EditorStyles.boldLabel);
        EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);

        showCreateTerrain = EditorGUILayout.Foldout(showCreateTerrain, "Create Terrain");
        if (showCreateTerrain)
        {
            GUILayout.Label("General Configuration", EditorStyles.boldLabel);

            EditorGUILayout.IntSlider(terrainSize, 33, 1000, new GUIContent("Terrain Size (X and Z)"));
            EditorGUILayout.IntSlider(terrainHeight, 5, 500, new GUIContent("Terrain Height (Y)"));
            EditorGUILayout.PropertyField(heightmapResolution, new GUIContent("Resolution"));

            GUILayout.Label("Terrain Presets", EditorStyles.boldLabel);

            showPresets = EditorGUILayout.Foldout(showPresets, "Terrain Presets");
            if (showPresets)
            {

                EditorGUILayout.PropertyField(presetTerrain, new GUIContent("Select Preset"));
                if (GUILayout.Button("Create Preset LandScape"))
                {

                    Debug.Log("Preset Landscape");
                    terrain.CreatePresetTerrain();
                }

            }
         

            GUILayout.Label("Custom Terrain Generation", EditorStyles.boldLabel);

            showCustomCreateTerrain = EditorGUILayout.Foldout(showCustomCreateTerrain, "Custom Terrain");
            if (showCustomCreateTerrain)
            {

               
                GUILayout.Label("Custom Terrain", EditorStyles.boldLabel);

                //EditorGUILayout.IntSlider(terrainHeight, 10, 500, new GUIContent("Terrain Height (Y)"));

                EditorGUILayout.PropertyField(baseAlgorithm, new GUIContent("Base Algorithm"));
                EditorGUILayout.IntSlider(numberMountains, 0, 15, new GUIContent("Number of Mountains"));
                EditorGUILayout.Slider(randomFactor, 0.0f, 1.0f,new GUIContent("Random Factor"));
                EditorGUILayout.Slider(hillyFactor, 0.0f, 1.0f, new GUIContent("Hilly Factor"));
                EditorGUILayout.Slider(smoothFactor, 0.0f, 1.0f, new GUIContent("Smooth Factor"));
                EditorGUILayout.PropertyField(erosionLevel, new GUIContent("Erosion Level"));
         
                if (GUILayout.Button("Create Custom Terrain"))
                {
                    Debug.Log("Creating custom terrain");
                    terrain.CreateCustomTerrain();
                }
            }
        }


        GUILayout.Label("Drawing Terrain", EditorStyles.boldLabel);
        EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);


        showDrawTerrain = EditorGUILayout.Foldout(showDrawTerrain, "Draw Terrain");
        if (showDrawTerrain)
        {
            GUILayout.Label("Water Configuration", EditorStyles.boldLabel);
            showWaterConfig = EditorGUILayout.Foldout(showWaterConfig, "Water Configuration");
            if (showWaterConfig) {
                //EditorGUILayout.Slider(seaLevel, 0, 1, new GUIContent("Sea Height"));
                EditorGUILayout.PropertyField(applyWater);
                EditorGUILayout.PropertyField(waterTexture);

              

            }

            GUILayout.Label("Drawing Terrain Presets", EditorStyles.boldLabel);

            showArid = EditorGUILayout.Foldout(showArid, "Arid Landscape");
            if (showArid)
            {

                if (GUILayout.Button("Apply Arid LandScape"))
                {
                    terrain.AridLandscape();
                }

            }
            showSnowy = EditorGUILayout.Foldout(showSnowy, "Snowy Landscape");
            if (showSnowy)
            {
                if (GUILayout.Button("Apply Snowy LandScape"))
                {
                    terrain.SnowyLandscape();
                }
            }
            showTropical = EditorGUILayout.Foldout(showTropical, "Tropical Landscape");
            if (showTropical)
            {
                if (GUILayout.Button("Apply Tropical LandScape"))
                {
                    terrain.TropicalLandscape();
                }

            }

            GUILayout.Label("Custom Textures", EditorStyles.boldLabel);


            showCustomDrawingData = EditorGUILayout.Foldout(showCustomDrawingData, "Custom Textures");
            if (showCustomDrawingData)
            {

                EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);
                GUILayout.Label("Custom Textures", EditorStyles.boldLabel);              
                splatMapTable = GUITableLayout.DrawTable(splatMapTable, serializedObject.FindProperty("splatHeightsList"));
                GUILayout.Space(70);

                EditorGUILayout.BeginHorizontal();
                if (GUILayout.Button("+"))
                {
                    terrain.AddNewSplatHeight();
                }
                if (GUILayout.Button("-"))
                {
                    terrain.RemoveSplatHeight();
                }

                EditorGUILayout.EndHorizontal();
                if (GUILayout.Button("Apply Custom Textures"))
                {
                    terrain.CustomTextures();
                }
            }

        }

        //Scrollbar ending code
        EditorGUILayout.EndScrollView();
        EditorGUILayout.EndVertical();

        serializedObject.ApplyModifiedProperties();
    }
    
}
