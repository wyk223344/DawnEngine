#pragma once

#include "GPUResource.h"
#include "Engine/Core/Include.h"
#include "Engine/Platform/Platform.h"

namespace DawnEngine
{
	class GPUSwapChain : GPUResource
	{
	public:

		//GPUSwapChain(Window* window)
		//	: m_Width(window->GetWidth())
		//	, m_Height(window->GetHeight())
		//	, m_Window(window)
		//{
		//}

		// 获取窗口宽度
		unsigned int GetWidth() const { return m_Width; }

		// 获取窗口高度
		unsigned int GetHeight() const { return m_Height; }

		// 获取绑定的窗口
		Window* GetWindow() const { return m_Window; }

	public:

		// 刷新交换链大小
		virtual void Resize(uint32 width, uint32 height) = 0;

	protected:

		unsigned int m_Width;
		unsigned int m_Height;

		Window* m_Window = nullptr;
	};
}