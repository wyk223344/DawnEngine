#pragma once

#include <vector>

namespace DawnEngine
{
	class MeshData;
	class MaterialBase;
	class Mesh;
	class GPUContext;

	class Model
	{
	public:

		bool InitGPUResource();

		void Draw(GPUContext* context);

		void AddMeshAndMaterial(MeshData* meshData, MaterialBase* material);

		std::vector<Mesh*>& GetMeshes() { return m_Meshes; }

		std::vector<MaterialBase*>& GetMaterials() { return m_Materials; }

	private:

		std::vector<MeshData*> m_MeshDatas;
		std::vector<MaterialBase*> m_Materials;
		std::vector<Mesh*> m_Meshes;

	};
}