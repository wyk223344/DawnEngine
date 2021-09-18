#pragma once

#include "Engine/Core/Include.h"

namespace DawnEngine
{
	class CopyLinearMaterial;
	class GPUTexture;
	class GPUContext;

	class ImGuiHelper : public Singleton<ImGuiHelper>
	{
	public:

		ImGuiHelper();

	public:

		bool Init();

		void Draw(GPUContext* context);

	private:

		CopyLinearMaterial* m_RenderMaterial;
		GPUTexture* m_FontTexture;
	};
}