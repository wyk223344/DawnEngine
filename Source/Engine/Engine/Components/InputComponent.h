#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Engine/Base/ComponentBase.h"

namespace DawnEngine
{
	using namespace Math;

	class InputComponent : public ComponentBase
	{
	protected:
		
		void Update() override;

	private:

		Vector2 m_PrePosition;
	};
}