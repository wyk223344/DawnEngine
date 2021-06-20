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

		// ��ȡ���ڿ��
		unsigned int GetWidth() const { return m_Width; }

		// ��ȡ���ڸ߶�
		unsigned int GetHeight() const { return m_Height; }

		// ��ȡ�󶨵Ĵ���
		Window* GetWindow() const { return m_Window; }

	public:

		// ˢ�½�������С
		virtual void Resize(uint32 width, uint32 height) = 0;

	protected:

		unsigned int m_Width;
		unsigned int m_Height;

		Window* m_Window = nullptr;
	};
}