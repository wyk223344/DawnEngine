
#include "Resource.h"
#include "Engine/Core/Include.h"
#include "Engine/Graphics/Models/Model.h"
#include "Engine/Graphics/Models/MeshData.h"
#include "Engine/Graphics/Textures/TextureData.h"
#include "Engine/Graphics/Materials/DefaultMaterial.h"
#include "Engine/Graphics/Materials/PBRMaterial.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "ThirdParty/tiny_obj_loader/tiny_obj_loader.h"

using namespace DawnEngine;
using namespace DawnEngine::Math;

MeshData& Resource::LoadMesh(std::string& filePath)
{
	LOG_INFO("[Resource] Start load mesh %s.", filePath);
    MeshData meshData;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;
	std::string dirPath = filePath;
	while (!dirPath.empty() && (dirPath.back() != '/'))
	{
		dirPath.pop_back();
	}
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str(), dirPath.c_str(), true);
	if (!ret)
	{
		LOG_ERROR("[Resource] Fail to load mesh %s.", filePath);
		return meshData;
	}
	std::vector<Vertex> vertices;
	std::vector<uint32> indices;
	
	

	LOG_INFO("[Resource] Finish load mesh %s.", filePath);
    return meshData;
}

TextureData& Resource::LoadTexture(std::string& filePath)
{
	LOG_INFO("[Resource] Start load texture %s.", filePath);
    TextureData textureData;
	LOG_INFO("[Resource] Finish load texture %s.", filePath);
    return textureData;
}


Model* Resource::LoadModel(const char* filePath)
{
	LOG_INFO("[Resource] Start load model %s.", filePath);
	
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;
	std::string dirPath = std::string(filePath);
	while (!dirPath.empty() && (dirPath.back() != '/'))
	{
		dirPath.pop_back();
	}
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath, dirPath.c_str(), true);
	if (!ret)
	{
		LOG_ERROR("[Resource] Fail to load model %s.", filePath);
		return nullptr;
	}
	Model* model = New<Model>();
	
	for (int i = 0; i < shapes.size(); i++)
	{
		tinyobj::mesh_t mesh = shapes[i].mesh;

		MeshData* meshData = New<MeshData>();

		for (int j = 0; j < mesh.indices.size(); j++)
		{
			tinyobj::index_t index = mesh.indices[j];
			int vertexIndex = index.vertex_index;
			int uvIndex = index.texcoord_index;
			int normalIndex = index.normal_index;
			float positionX = vertexIndex >= 0 ? attrib.vertices[vertexIndex * 3] : 0.0f;
			float positionY = vertexIndex >= 0 ? attrib.vertices[vertexIndex * 3 + 1] : 0.0f;
			float positionZ = vertexIndex >= 0 ? attrib.vertices[vertexIndex * 3 + 2] : 0.0f;
			float u = uvIndex >= 0 ? attrib.texcoords[uvIndex * 2] : 0.0f;
			float v = uvIndex >= 0 ? attrib.texcoords[uvIndex * 2 + 1] : 0.0f;
			float normalX = normalIndex >= 0 ? attrib.normals[normalIndex * 3] : 0.0f;
			float normalY = normalIndex >= 0 ? attrib.normals[normalIndex * 3 + 1] : 1.0f;
			float normalZ = normalIndex >= 0 ? attrib.normals[normalIndex * 3 + 2] : 0.0f;
			meshData->Indices.push_back(meshData->Vertices.size());
			meshData->Vertices.push_back(Vertex(positionX, positionY, positionZ, u, v, normalX, normalY, normalZ));
		}

		MaterialBase* material = New<DefaultMaterial>(Color::Blue);;

		model->AddMeshAndMaterial(meshData, material);
	}

	LOG_INFO("[Resource] Finish load model %s.", filePath);
	return model;
}