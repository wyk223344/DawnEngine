#pragma once


#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"
#include "Engine/Graphics/Materials/MaterialBase.h"
#include "Engine/Graphics/Models/Mesh.h"

namespace DawnEngine
{
	class GPUContext;

	class MeshRendererComponent : public ComponentBase
	{
	public:

		MeshRendererComponent(EntityBase* entity, Mesh* mesh, MaterialBase* material)
			: ComponentBase(entity)
			, m_Mesh(mesh)
			, m_Material(material)
		{
		}

		void Render(GPUContext* context);

	private:

		Mesh* m_Mesh;
		MaterialBase* m_Material;
	};
}