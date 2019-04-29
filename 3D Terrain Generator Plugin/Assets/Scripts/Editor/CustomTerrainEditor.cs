using UnityEditor;
using UnityEngine;
using EditorGUITable;

[CustomEditor(typeof(CustomTerrain))]
[CanEditMultipleObjects]

public class CustomTerrainEditor : Editor
{
    GUITableState splatMapTable;
    SerializedProperty SplatHeights;
    
    

    bool showDrawTerrain = false;
    bool showCustomDrawingData = false;
    bool showSnowy = false;
    bool showTropical = false;
    bool showArid = false;

    void OnEnable() {

        splatMapTable = new GUITableState("splatMapTable");
        SplatHeights = serializedObject.FindProperty("SplatHeights");

       


    }

    Vector2 scrollPos;
    //Graphical User Interface on the editor
    public override void OnInspectorGUI() {

        serializedObject.Update();

        CustomTerrain terrain = (CustomTerrain)target;


        //Scrollbar Starting Code
        Rect r = EditorGUILayout.BeginVertical();
        scrollPos =
            EditorGUILayout.BeginScrollView(scrollPos, GUILayout.Width(r.width), GUILayout.Height(r.height));
        EditorGUI.indentLevel++;



        showDrawTerrain = EditorGUILayout.Foldout(showDrawTerrain, "Draw Terrain");
        if (showDrawTerrain)
        {

            showArid = EditorGUILayout.Foldout(showArid, "Arid Landscape");
            if (showArid) {

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
                GUILayout.Space(200);
                
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
