#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"

namespace DawnEngine
{
	using namespace DawnEngine::Math;

	class TransformComponent : ComponentBase
	{
	public:

		void SetPosition(Vector3& position)
		{
			m_Transform.Translation = position;
		}

		void LookAt(Vector3& target)
		{
			m_Transform.LookAt(target);
		}



	private:

		Transform m_Transform;
	};
}