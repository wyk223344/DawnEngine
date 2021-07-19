
#include "Resource.h"
#include "Engine/Core/Include.h"
#include "Engine/Graphics/Models/Model.h"
#include "Engine/Graphics/Models/MeshData.h"
#include "Engine/Graphics/Textures/TextureData.h"
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


Model* Resource::LoadModel(std::string& filePath)
{
	LOG_INFO("[Resource] Start load model %s.", filePath);
	
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
		LOG_ERROR("[Resource] Fail to load model %s.", filePath);
		return nullptr;
	}

	for (int i = 0; i < shapes.size(); i++)
	{
		MeshData meshData;


	}

	LOG_INFO("[Resource] Finish load model %s.", filePath);
	return nullptr;
}