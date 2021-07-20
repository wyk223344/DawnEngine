#pragma once

#include <string>

namespace DawnEngine
{
	class MeshData;
	class TextureData;
	class Model;

	class Resource
	{
	public:

		static MeshData& LoadMesh(std::string& filePath);

		static TextureData& LoadTexture(std::string& filePath);

		static Model* LoadModel(const char* filePath);
	};
}