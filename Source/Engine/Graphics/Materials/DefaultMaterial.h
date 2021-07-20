#pragma once

#include "Engine/Core/Include.h"
#include "MaterialBase.h"
#include "Engine/Graphics/GPUConstantBuffer.h"

namespace DawnEngine
{
	class DefaultMaterial : public MaterialBase
	{
	public:

		DefaultMaterial(Color color);

		bool InitGPUResource() override;

		void Draw(GPUContext* context) override;

	private:

		DefaultMaterialConstants m_ConstantInfo;

	};
}