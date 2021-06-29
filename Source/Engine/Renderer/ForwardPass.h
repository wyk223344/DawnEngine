#pragma once

#include "RendererPassBase.h"

namespace DawnEngine
{
	class GPUContext;

	class ForwardPass : public RenderPassBase<ForwardPass>
	{
	public:

		void Render(GPUContext* context);
	};
}