#pragma once
#include "PreRequisitos.h"
#include "fbxsdk.h"

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	bool LoadModel(const std::string& filePath);
	const std::vector<SimpleVertex>& GetVertices() const { return vertices; }
	const std::vector<uint32_t>& GetIndices() const { return indices; }

	std::vector<std::string>GetTextureFileName() const { return textureFileName; }

	void ProcessNode(FbxNode* node);
	void ProcessMesh(FbxNode* node);


	void ProcessMaterial(FbxSurfaceMaterial* material);
private:
	FbxManager* lSdkManager;
	FbxScene* lScene;
	std::vector<SimpleVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::string> textureFileName;
public:
	std::vector<Mesh> meshes;
};

