#pragma once

#include "Engine/Engine/Base/EntityBase.h"
#include "Engine/Engine/Components/LightComponent.h"
#include "Engine/Engine/Components/TransformComponent.h"

namespace DawnEngine
{
	class LightEntity : public EntityBase
	{
	public:

		LightEntity()
			: EntityBase()
		{
			AddComponent<TransformComponent>();
			AddComponent<LightComponent>();
		}
	};
}