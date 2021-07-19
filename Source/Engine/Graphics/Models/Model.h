#pragma once

#include <vector>

namespace DawnEngine
{
	class MeshData;
	class MaterialBase;

	class Model
	{
	public:



	private:

		std::vector<MeshData> m_MeshDatas;
		std::vector<MaterialBase> m_Materials;

	};
}