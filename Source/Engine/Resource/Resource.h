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

		static TextureData* LoadTexture(const char* filePath);

		static TextureData* LoadCubeMap(const char* filePath);

		static Model* LoadModel(const char* filePath);
	};
}