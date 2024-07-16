#pragma once
#include "PreRequisitos.h"
#include "fbxsdk.h"

class ModelLoader
{
public:
    // Constructor
    ModelLoader();
    // Destructor
    ~ModelLoader();

    // M�todo para cargar un modelo desde un archivo
    bool LoadModel(const std::string& filePath);

    // M�todo para obtener los v�rtices cargados
    const std::vector<SimpleVertex>& GetVertices() const { return vertices; }

    // M�todo para obtener los �ndices cargados
    const std::vector<uint32_t>& GetIndices() const { return indices; }

    // M�todo para obtener los nombres de archivos de texturas
    std::vector<std::string> GetTextureFileName() const { return textureFileName; }

    // M�todo para procesar un nodo del modelo
    void ProcessNode(FbxNode* node);

    // M�todo para procesar una malla del modelo
    void ProcessMesh(FbxNode* node);

    // M�todo para procesar un material del modelo
    void ProcessMaterial(FbxSurfaceMaterial* material);

private:
    // Puntero al administrador del SDK de FBX
    FbxManager* lSdkManager;

    // Puntero a la escena de FBX
    FbxScene* lScene;

    // Vector de v�rtices del modelo
    std::vector<SimpleVertex> vertices;

    // Vector de �ndices del modelo
    std::vector<unsigned int> indices;

    // Vector de nombres de archivos de texturas
    std::vector<std::string> textureFileName;

public:
    // Vector de mallas del modelo
    std::vector<Mesh> meshes;
};


