#pragma once


#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"


namespace DawnEngine
{
	class GPUContext;
	class Model;

	class MeshRendererComponent : public ComponentBase
	{
	public:

		MeshRendererComponent(EntityBase* entity, Model* model)
			: ComponentBase(entity)
			, m_Model(model)
		{
		}

		void Start() override;

		void Render(GPUContext* context);

		Model* GetModel() const { return m_Model; }

	private:

		Model* m_Model;

	};
}