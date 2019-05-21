using UnityEditor;
using UnityEngine;
using EditorGUITable;

[CustomEditor(typeof(Terrain3D))]
public class Terrain3DEditor : Editor
{
    GUITableState splatMapTable;
    SerializedProperty SplatHeights;

    SerializedProperty waterTexture;
    SerializedProperty seaLevel;
    SerializedProperty applyWater;



    bool showWaterConfig = false;

    bool showCreateTerrain = false;
    bool showHilly = false;
    bool showSoft = false;
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



    }

    Vector2 scrollPos;
    //Graphical User Interface on the editor
    public override void OnInspectorGUI()
    {

        serializedObject.Update();

        Terrain3D terrain = (Terrain3D)target;


        //Scrollbar Starting Code
        Rect r = EditorGUILayout.BeginVertical();
        scrollPos =
            EditorGUILayout.BeginScrollView(scrollPos, GUILayout.Width(r.width), GUILayout.Height(r.height));
        EditorGUI.indentLevel++;

        GUILayout.Label("Terrain Generation", EditorStyles.boldLabel);
        EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);

        showCreateTerrain = EditorGUILayout.Foldout(showCreateTerrain, "Create Terrain");
        if (showCreateTerrain)
        {
            GUILayout.Label("Terrain Presets", EditorStyles.boldLabel);

            showHilly = EditorGUILayout.Foldout(showHilly, "Hilly Landscape");
            if (showHilly)
            {

                if (GUILayout.Button("Create Hilly LandScape"))
                {
                    Debug.Log("Hilly LandsScape");
                }

            }
            showSoft = EditorGUILayout.Foldout(showSoft, "Soft Landscape");
            if (showSoft)
            {
                if (GUILayout.Button("Create Soft LandScape"))
                {
                    Debug.Log("Soft LandScape");
                }
            }

            GUILayout.Label("Custom Terrain Generation", EditorStyles.boldLabel);

            showCustomCreateTerrain = EditorGUILayout.Foldout(showCustomCreateTerrain, "Custom Terrain");
            if (showCustomCreateTerrain)
            {

                //EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);
                GUILayout.Label("Custom Terrain", EditorStyles.boldLabel);
                /*EditorGUILayout.Slider(splatOffset, 0, 0.1f, new GUIContent("Offset"));
                EditorGUILayout.Slider(splatNoiseXScale, 0.001f, 1, new GUIContent("Noise X Scale"));
                EditorGUILayout.Slider(splatNoiseYScale, 0.001f, 1, new GUIContent("Noise Y Scale"));
                EditorGUILayout.Slider(splatNoiseScaler, 0, 1, new GUIContent("Noise Scaler"));*/
                // splatMapTable = GUITableLayout.DrawTable(splatMapTable, serializedObject.FindProperty("splatHeightsList"));
                // GUILayout.Space(200);

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
                if (GUILayout.Button("Create Custom Terrain"))
                {
                    Debug.Log("Creating custom terrain");
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

                /*if (GUILayout.Button("Apply Water")) {
                    terrain.ApplyWater();
                }*/

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
                /*EditorGUILayout.Slider(splatOffset, 0, 0.1f, new GUIContent("Offset"));
                EditorGUILayout.Slider(splatNoiseXScale, 0.001f, 1, new GUIContent("Noise X Scale"));
                EditorGUILayout.Slider(splatNoiseYScale, 0.001f, 1, new GUIContent("Noise Y Scale"));
                EditorGUILayout.Slider(splatNoiseScaler, 0, 1, new GUIContent("Noise Scaler"));*/
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


    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }
}
