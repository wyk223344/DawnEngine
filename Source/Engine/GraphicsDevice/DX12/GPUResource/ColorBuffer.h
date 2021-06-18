#pragma once

#if GRAPHICS_API_DIRECTX12

#include "PixelBuffer.h"
#include "Engine/Core/Include.h"


namespace DawnEngine::DX12
{
	/*	
		颜色缓冲区
		对像素缓冲区进一步封装，规格每个像素中存储的是颜色值

		维护视图：
		m_SRVHandle: 着色器资源视图
		m_RTVHandle: 渲染目标视图			！！通过Create创建的缓冲区才会创建该视图
		m_UAVHandle[12]: 无序访问视图		！！通过Create创建的缓冲区才会创建该视图

		CreateFromSwapChain： 封装交换链的缓冲区
		Create: 直接创建缓冲区
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