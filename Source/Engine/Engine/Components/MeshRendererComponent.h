#pragma once


#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"
#include "Engine/Graphics/Materials/MaterialBase.h"
#include "Engine/Graphics/Models/GPUMesh.h"

namespace DawnEngine
{
	class GPUContext;

	class MeshRendererComponent : public ComponentBase
	{
	public:

		MeshRendererComponent(EntityBase* entity, GPUMesh* mesh, MaterialBase* material)
			: ComponentBase(entity)
			, m_Mesh(mesh)
			, m_Material(material)
		{
		}

		void Render(GPUContext* context);

	private:

		GPUMesh* m_Mesh;
		MaterialBase* m_Material;
	};
}