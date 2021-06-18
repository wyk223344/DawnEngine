#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/GraphicsDevice/DX12/IncludeDX12Headers.h"
#include "GPUResource.h"


namespace DawnEngine::DX12
{
	/// <summary>
	/// 像素缓冲区
	/// 对于资源来说，很多就是gpu中的一块内存，可以叫buff、缓冲区等
	/// 这里实现的就是像素缓冲区，规定该buff个结构是像素类型，规定了每个像素的格式
	/// </summary>
	class PixelBuffer : public GPUResource
	{
	public:
		PixelBuffer() : 
			m_Width(0),
			m_Height(0),
			m_ArraySize(0),
			m_Format(DXGI_FORMAT_UNKNOWN),
			m_BankRotation(0) 
		{
		}

		uint32 GetWidth(void) const { return m_Width; }
		uint32 GetHeight(void) const { return m_Height; }
		uint32 GetDepth(void) const { return m_ArraySize; }
		const DXGI_FORMAT& GetFormat(void) const { return m_Format; }

	protected:

		// 生成2d纹理描述
		D3D12_RESOURCE_DESC DescribeTex2D(uint32 width, uint32 height, uint32 arraySize, uint32 numMips, DXGI_FORMAT format, uint32 flags);

		// 把现成的Resource管理起来
		void AssociateWithResource(ID3D12Device* device, const std::wstring& name, ID3D12Resource* resource, D3D12_RESOURCE_STATES currentState);

		// 生成一个纹理资源
		void CreateTextureResource(ID3D12Device* device, const std::wstring& name, const D3D12_RESOURCE_DESC& resourceDesc,
			D3D12_CLEAR_VALUE clearValue, D3D12_GPU_VIRTUAL_ADDRESS virtualAddress = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN);
	
	protected:

		// 获得每个像素有多少个字节
		static size_t BytesPerPixel(DXGI_FORMAT format);

#pragma region 主要是对像素格式的一些转换，方便一些操作
		static DXGI_FORMAT GetBaseFormat(DXGI_FORMAT format);
		static DXGI_FORMAT GetUAVFormat(DXGI_FORMAT format);
		static DXGI_FORMAT GetDSVFormat(DXGI_FORMAT format);
		static DXGI_FORMAT GetDepthFormat(DXGI_FORMAT format);
		static DXGI_FORMAT GetStencilFormat(DXGI_FORMAT format);
#pragma endregion

	protected:  
		uint32 m_Width;
		uint32 m_Height;
		uint32 m_ArraySize;
		DXGI_FORMAT m_Format;
		uint32 m_BankRotation;
	};

}


#endif