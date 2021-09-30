#pragma once

#include "Engine/Core/Include.h"

namespace DawnEngine
{
	class CopyLinearMaterial;
	class GPUTexture;
	class GPUContext;
	class RenderContext;

	class ImGuiHelper : public Singleton<ImGuiHelper>
	{
	public:

		ImGuiHelper();

	public:

		bool Init();

		void SetDisplaySize(int width, int height, float scaleX = 1.0f, float scaleY = 1.0f);

		void BeforeDraw(RenderContext* renderContext);

		void AfterDraw(RenderContext* renderContext);

		void Draw(RenderContext* renderContext);

	private:

		CopyLinearMaterial* m_RenderMaterial;
		GPUTexture* m_FontTexture;
	};
}