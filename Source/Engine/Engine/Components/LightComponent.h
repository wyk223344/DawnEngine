#pragma once


#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"

namespace DawnEngine
{
	class DirectionalLight;

	class LightComponent : public ComponentBase
	{
	public:

		void CreateDirectionalLight();

		DirectionalLight* GetDirectionalLight();

	private:

		DirectionalLight* m_DirectionalLight;

	};
}