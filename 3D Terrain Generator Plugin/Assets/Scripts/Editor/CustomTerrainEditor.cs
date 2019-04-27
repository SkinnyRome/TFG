using UnityEditor;
using UnityEngine;
using EditorGUITable;

[CustomEditor(typeof(CustomTerrain))]
[CanEditMultipleObjects]

public class CustomTerrainEditor : Editor
{
    GUITableState splatMapTable;
    SerializedProperty splatHeights;


    bool showSplatMaps = false;


    void OnEnable() {

        splatMapTable = new GUITableState("splatMapTable");
        splatHeights = serializedObject.FindProperty("splatHeights");


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



        showSplatMaps = EditorGUILayout.Foldout(showSplatMaps, "Splat Maps");
        if (showSplatMaps)
        {
            EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);
            GUILayout.Label("Splat Maps", EditorStyles.boldLabel);
            /*EditorGUILayout.Slider(splatOffset, 0, 0.1f, new GUIContent("Offset"));
            EditorGUILayout.Slider(splatNoiseXScale, 0.001f, 1, new GUIContent("Noise X Scale"));
            EditorGUILayout.Slider(splatNoiseYScale, 0.001f, 1, new GUIContent("Noise Y Scale"));
            EditorGUILayout.Slider(splatNoiseScaler, 0, 1, new GUIContent("Noise Scaler"));*/
            splatMapTable = GUITableLayout.DrawTable(splatMapTable,
                                            serializedObject.FindProperty("splatHeights"));
            GUILayout.Space(20);
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
            if (GUILayout.Button("Apply SplatMaps"))
            {
                terrain.SplatMaps();
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
