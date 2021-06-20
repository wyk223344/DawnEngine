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

		// ��ʼ��������
		virtual bool InitSwapChain();

		// ��ȡ��ʾ�����
		virtual void* GetNativePtr() const = 0;

		// ��ȡ���ڿ��
		unsigned int GetWidth() const { return m_Width; }

		// ��ȡ���ڸ߶�
		unsigned int GetHeight() const { return m_Height; }

		// ��ȡ������
		GPUSwapChain* GetSwapChain() const { return m_SwapChain; }

	protected:

		unsigned int m_Width;
		unsigned int m_Height;

		GPUSwapChain* m_SwapChain;


	};

}