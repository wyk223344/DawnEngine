
#include "Resource.h"
#include "Engine/Core/Include.h"
#include "Engine/Graphics/Models/Model.h"
#include "Engine/Graphics/Models/MeshData.h"
#include "Engine/Graphics/Textures/TextureData.h"
#include "Engine/Graphics/Materials/DefaultMaterial.h"
#include "Engine/Graphics/Materials/PBRMaterial.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "ThirdParty/tiny_obj_loader/tiny_obj_loader.h"

#include "ThirdParty/stb_image/stb_image.h"

using namespace DawnEngine;
using namespace DawnEngine::Math;



TextureData* Resource::LoadTexture(const char* filePath)
{
	//std::string projectPath = std::string(PROJECT_SOURCE_ROOT);
	std::string projectPath = std::string("D:/WorkSpace/DawnEngine/");
	std::string filePathStr = std::string(filePath);
	std::string tempStr = projectPath + filePathStr;
	const char* finalPath = tempStr.c_str();

	LOG_INFO("[Resource] Start load texture %s.", finalPath);

	FILE* f;
	int fResult = fopen_s(&f, finalPath, "rb");
	if (!f || fResult != 0)
	{
		LOG_ERROR("Can't load file! %d", fResult);
		f = 0;
	}
	else
	{
		fclose(f);
	}
	std::cout << finalPath << std::endl;
	TextureData* textureData = New<TextureData>();
	textureData->Data = stbi_load(
		finalPath,
		&textureData->Width, 
		&textureData->Height, 
		&textureData->Channel, 
		4);
	
	std::cout << finalPath << std::endl;
	LOG_INFO("[Resource] Finish load texture %s.", finalPath);
	LOG_INFO("[Resource] Finish load texture Width: %d , Height: %d, Channel: %d",
		textureData->Width,
		textureData->Height,
		textureData->Channel);

	textureData->Channel = 4;
    return textureData;
}


TextureData* Resource::LoadCubeMap(const char* filePath)
{
	//std::string projectPath = std::string(PROJECT_SOURCE_ROOT);
	LOG_INFO("[Resource] Start load cubemap %s.", filePath);
	std::string filePathStr = std::string(filePath);
	TextureData* textureData = New<TextureData>();
	textureData->Subresources.push_back(LoadTexture((filePathStr + "right.jpg").c_str()));
	textureData->Subresources.push_back(LoadTexture((filePathStr + "left.jpg").c_str()));
	textureData->Subresources.push_back(LoadTexture((filePathStr + "top.jpg").c_str()));
	textureData->Subresources.push_back(LoadTexture((filePathStr + "bottom.jpg").c_str()));
	textureData->Subresources.push_back(LoadTexture((filePathStr + "front.jpg").c_str()));
	textureData->Subresources.push_back(LoadTexture((filePathStr + "back.jpg").c_str()));
	textureData->Width = textureData->Subresources[0]->Width;
	textureData->Height = textureData->Subresources[0]->Height;
	textureData->Channel = textureData->Subresources[0]->Channel;
	LOG_INFO("[Resource] Finish load cubemap %s.", filePath);
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