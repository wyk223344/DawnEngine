#pragma once

#include "MaterialBase.h"


namespace DawnEngine
{
	class ShadowMaterial : public MaterialBase
	{
	public:

		ShadowMaterial();

		bool InitGPUResource() override;

		void Draw(GPUContext* context) override;
	};
}