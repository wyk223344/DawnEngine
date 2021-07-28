#pragma once

#include "RendererPassBase.h"

namespace DawnEngine
{
	class GPUContext;
	class RenderContext;

	class LightPass : public RenderPassBase<LightPass>
	{
	public:

		void Init();

		void Render(RenderContext* renderContext);

		void Dispose();
	};
}