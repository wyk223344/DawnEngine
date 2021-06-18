#pragma once

#if GRAPHICS_API_DIRECTX12

#include "PixelBuffer.h"
#include "Engine/Core/Include.h"


namespace DawnEngine::DX12
{
	/*	
		��ɫ������
		�����ػ�������һ����װ�����ÿ�������д洢������ɫֵ

		ά����ͼ��
		m_SRVHandle: ��ɫ����Դ��ͼ
		m_RTVHandle: ��ȾĿ����ͼ			����ͨ��Create�����Ļ������Żᴴ������ͼ
		m_UAVHandle[12]: ���������ͼ		����ͨ��Create�����Ļ������Żᴴ������ͼ

		CreateFromSwapChain�� ��װ�������Ļ�����
		Create: ֱ�Ӵ���������
	*/
	class ColorBuffer : public PixelBuffer
	{
	public:

	protected:
	protected:
		Color m_ClearColor;
		D3D12_CPU_DESCRIPTOR_HANDLE m_SRVHandle;
		D3D12_CPU_DESCRIPTOR_HANDLE m_RTVHandle;
		D3D12_CPU_DESCRIPTOR_HANDLE m_UAVHandle[12];
		uint32 m_NumMipMaps;
		uint32 m_FragmentCount;
		uint32 m_SampleCount;
	};

}

#endif