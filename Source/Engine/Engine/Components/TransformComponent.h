#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"

namespace DawnEngine
{
	class TransformComponent : ComponentBase
	{

	private:

		Math::Transform m_Transform;
	};
}