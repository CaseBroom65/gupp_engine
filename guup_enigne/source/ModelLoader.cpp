#include "ModelLoader.h"

ModelLoader::ModelLoader() : lSdkManager(nullptr), lScene(nullptr){
    // Inicialización del SDK manager
    lSdkManager = FbxManager::Create();
    if (!lSdkManager){
        ERROR("ModelLoader", "FbxManager::()", "Unable to create FBX Manager!");
    }
    else{
        MESSAGE("ModelLoader", "ModelLoader", "Autodesk FBX SDK version: " << lSdkManager->GetVersion());
    }

    // Crear los objetos de IOSettings
    FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    // Crear la escena FBX
    lScene = FbxScene::Create(lSdkManager, "myScene");
}

ModelLoader::~ModelLoader(){
    if (lSdkManager)
        lSdkManager->Destroy();
}

bool ModelLoader::LoadModel(const std::string& filePath){
    // Crear e importar los SDK manager en uso
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

    // Usar el primer argumento del filename para importar
    if (!lImporter->Initialize(filePath.c_str(), -1, lSdkManager->GetIOSettings())){
        MESSAGE("ModelLoader", "LoadModel", "Unable to initialize FBX importer for file: " << filePath.c_str());
        ERROR("ModelLoader", "LoadModel", "Error returned: " << lImporter->GetStatus().GetErrorString());
        return false;
    }

    // Importar la escena
    if (!lImporter->Import(lScene)){
        ERROR("ModelLoader", "lImporter->Import", "Unable to import the FBX Scene from file: " << filePath.c_str());
        lImporter->Destroy();
        return false;
    }

    // Destruir el importador
    lImporter->Destroy();
    MESSAGE("ModelLoader", "LoadModel", "Successfully imported the FBX scene from file: " << filePath.c_str());

    // Procesar la escena
    FbxNode* lrootNode = lScene->GetRootNode();
    if (lrootNode){
        for (int i = 0; i < lrootNode->GetChildCount(); i++){
            ProcessNode(lrootNode->GetChild(i));
        }
    }

    // Procesar materiales
    int materialCount = lScene->GetMaterialCount();
    for (int i = 0; i < materialCount; ++i){
        FbxSurfaceMaterial* material = lScene->GetMaterial(i);
        ProcessMaterial(material);
    }

    // Se puede procesar la escena según sea necesario
    return true;
}

void ModelLoader::ProcessNode(FbxNode* node){
    // Verifica si el nodo tiene atributos y si es un mesh
    if (node->GetNodeAttribute()){
        if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh){
            ProcessMesh(node);
        }
    }
    // Recursivamente procesa los nodos hijos
    for (int i = 0; i < node->GetChildCount(); i++){
        ProcessNode(node->GetChild(i));
    }
}

void ModelLoader::ProcessMesh(FbxNode* node){
    FbxMesh* mesh = node->GetMesh();
    if (!mesh) return;

    std::vector<SimpleVertex> vertices;
    std::vector<UINT> indices;

    // Procesar vértices y normales
    for (int i = 0; i < mesh->GetControlPointsCount(); i++) {
        FbxVector4* controlPoint = mesh->GetControlPoints();
        SimpleVertex vertex;
        vertex.Pos = XMFLOAT3((float)controlPoint[i][0],
            (float)controlPoint[i][1],
            (float)controlPoint[i][2]);
        vertices.push_back(vertex);
    }

    // Procesar UVs
    if (mesh->GetElementUVCount() > 0) {
        FbxGeometryElementUV* uvElement = mesh->GetElementUV(0);
        FbxGeometryElement::EMappingMode mappingMode = uvElement->GetMappingMode();
        FbxGeometryElement::EReferenceMode referenceMode = uvElement->GetReferenceMode();
        int polyIndexCounter = 0;

        for (int polyIndex = 0; polyIndex < mesh->GetPolygonCount(); polyIndex++) {
            int polySize = mesh->GetPolygonSize(polyIndex);
            for (int vertIndex = 0; vertIndex < polySize; vertIndex++) {
                int controlPointIndex = mesh->GetPolygonVertex(polyIndex, vertIndex);

                int uvIndex = -1;
                if (mappingMode == FbxGeometryElement::eByControlPoint) {
                    if (referenceMode == FbxGeometryElement::eDirect) {
                        uvIndex = controlPointIndex;
                    }
                    else if (referenceMode == FbxGeometryElement::eIndexToDirect) {
                        uvIndex = uvElement->GetIndexArray().GetAt(controlPointIndex);
                    }
                }
                else if (mappingMode == FbxGeometryElement::eByPolygonVertex) {
                    if (referenceMode == FbxGeometryElement::eDirect || referenceMode == FbxGeometryElement::eIndexToDirect){
                        uvIndex = uvElement->GetIndexArray().GetAt(polyIndexCounter);
                        polyIndexCounter++;
                    }
                }

                if (uvIndex != -1) {
                    FbxVector2 uv = uvElement->GetDirectArray().GetAt(uvIndex);
                    vertices[controlPointIndex].Tex = XMFLOAT2((float)uv[0], -(float)uv[1]);
                }
            }
        }
    }

    // Procesar índices
    for (int i = 0; i < mesh->GetPolygonCount(); i++) {
        for (int j = 0; j < mesh->GetPolygonSize(i); j++) {
            indices.push_back(mesh->GetPolygonVertex(i, j));
        }
    }

    // Almacenar datos del mesh
    MeshComponent meshData;
    meshData.m_vertex = vertices;
    meshData.m_index = indices;
    meshData.m_name = node->GetName();
    meshData.m_numVertex = vertices.size();
    meshData.m_numIndex = indices.size();

    meshes.push_back(meshData);
}

void ModelLoader::ProcessMaterial(FbxSurfaceMaterial* material){
    if (material){
        FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
        if (prop.IsValid()){
            int textureCount = prop.GetSrcObjectCount<FbxTexture>();
            for (int i = 0; i < textureCount; ++i){
                FbxTexture* texture = FbxCast<FbxTexture>(prop.GetSrcObject<FbxTexture>(i));
                if (texture){
                    textureFileName.push_back(texture->GetName());
                }
            }
        }
    }
}
