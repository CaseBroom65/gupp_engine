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

    // Método para cargar un modelo desde un archivo
    bool LoadModel(const std::string& filePath);

    // Método para obtener los vértices cargados
    const std::vector<SimpleVertex>& GetVertices() const { return vertices; }

    // Método para obtener los índices cargados
    const std::vector<uint32_t>& GetIndices() const { return indices; }

    // Método para obtener los nombres de archivos de texturas
    std::vector<std::string> GetTextureFileName() const { return textureFileName; }

    // Método para procesar un nodo del modelo
    void ProcessNode(FbxNode* node);

    // Método para procesar una malla del modelo
    void ProcessMesh(FbxNode* node);

    // Método para procesar un material del modelo
    void ProcessMaterial(FbxSurfaceMaterial* material);

private:
    // Puntero al administrador del SDK de FBX
    FbxManager* lSdkManager;

    // Puntero a la escena de FBX
    FbxScene* lScene;

    // Vector de vértices del modelo
    std::vector<SimpleVertex> vertices;

    // Vector de índices del modelo
    std::vector<unsigned int> indices;

    // Vector de nombres de archivos de texturas
    std::vector<std::string> textureFileName;

public:
    // Vector de mallas del modelo
    std::vector<Mesh> meshes;
};


