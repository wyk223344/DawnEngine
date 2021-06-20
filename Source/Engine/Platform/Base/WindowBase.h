#pragma once

#include "Engine/Platform/CreateWindowSettings.h"
#include "Engine/Graphics/GPUSwapChain.h"


namespace DawnEngine
{

	class WindowBase
	{
	protected:

		explicit WindowBase(const CreateWindowSettings& settings);
		virtual ~WindowBase();

	public:

		// 初始化交换链
		virtual bool InitSwapChain();

		// 获取显示窗句柄
		virtual void* GetNativePtr() const = 0;

		// 获取窗口宽度
		unsigned int GetWidth() const { return m_Width; }

		// 获取窗口高度
		unsigned int GetHeight() const { return m_Height; }

		// 获取交换链
		GPUSwapChain* GetSwapChain() const { return m_SwapChain; }

	protected:

		unsigned int m_Width;
		unsigned int m_Height;

		GPUSwapChain* m_SwapChain;


	};

}