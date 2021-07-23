#pragma once

#include "RendererPassBase.h"

namespace DawnEngine
{
	class GPUContext;
	class RenderContext;

	class ForwardPass : public RenderPassBase<ForwardPass>
	{
	public:

		void Init();
		
		void Render(RenderContext* renderContext);

		void Dispose();
	};
}