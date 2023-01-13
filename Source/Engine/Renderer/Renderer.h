#pragma once

#include "Engine/Engine/EngineService.h"

namespace DawnEngine
{
	class GPUContext;
	class GPUTexture;
	class RenderContext;

	class Renderer
	{
	public:
		static void Render(GPUContext* context);

		static RenderContext* GetRenderContext();
	};

	class RendererService : public EngineService
	{
	public:

		RendererService();

		bool Init() override;
		void Dispose() override;
	};
}