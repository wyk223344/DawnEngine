#pragma once

#include "MaterialBase.h"
#include "Engine/Graphics/GPUConstantBuffer.h"

namespace DawnEngine
{
	class PBRMaterial : public MaterialBase
	{
	public:

		PBRMaterial();

		bool InitGPUResource() override;

		void Draw(GPUContext* context) override;

	private:

		PBRMaterialConstants m_ConstantInfo;
	};
}