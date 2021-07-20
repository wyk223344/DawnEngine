#pragma once

#include "Engine/Engine/Base/EntityBase.h"
#include "Engine/Engine/Components/MeshRendererComponent.h"
#include "Engine/Engine/Components/TransformComponent.h"

namespace DawnEngine
{
	class Model;

	class RenderEntity : public EntityBase
	{
	public:
		RenderEntity(Model* model)
			: EntityBase()
		{
			AddComponent<TransformComponent>();
			AddComponent<MeshRendererComponent>(model);
		}
	};
}