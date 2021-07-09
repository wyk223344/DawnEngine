#pragma once

#include "Engine/Engine/Base/EntityBase.h"
#include "Engine/Engine/Components/CameraComponent.h"
#include "Engine/Engine/Components/TransformComponent.h"
#include "Engine/Engine/Components/InputComponent.h"

namespace DawnEngine
{
	class CameraEntity : public EntityBase
	{
	public:

		CameraEntity(float fov, float aspect)
			: EntityBase()
		{
			AddComponent<TransformComponent>();
			AddComponent<InputComponent>();
			AddComponent<CameraComponent>(fov, aspect);
		}
	};
}