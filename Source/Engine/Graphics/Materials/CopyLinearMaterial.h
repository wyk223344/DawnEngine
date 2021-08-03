#pragma once

#include "MaterialBase.h"

namespace DawnEngine
{

	class GPUTexture;

	class CopyLinearMaterial : public MaterialBase
	{
	public:

		CopyLinearMaterial();

		bool InitGPUResource() override;

		void Draw(GPUContext* context) override;

	public:

		GPUTexture* SrcTexture;
	};
}