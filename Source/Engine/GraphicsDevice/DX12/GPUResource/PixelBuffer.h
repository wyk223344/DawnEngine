#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/GraphicsDevice/DX12/IncludeDX12Headers.h"
#include "GPUResource.h"


namespace DawnEngine::DX12
{
	/// <summary>
	/// ���ػ�����
	/// ������Դ��˵���ܶ����gpu�е�һ���ڴ棬���Խ�buff����������
	/// ����ʵ�ֵľ������ػ��������涨��buff���ṹ���������ͣ��涨��ÿ�����صĸ�ʽ
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

		// ����2d��������
		D3D12_RESOURCE_DESC DescribeTex2D(uint32 width, uint32 height, uint32 arraySize, uint32 numMips, DXGI_FORMAT format, uint32 flags);

		// ���ֳɵ�Resource��������
		void AssociateWithResource(ID3D12Device* device, const std::wstring& name, ID3D12Resource* resource, D3D12_RESOURCE_STATES currentState);

		// ����һ��������Դ
		void CreateTextureResource(ID3D12Device* device, const std::wstring& name, const D3D12_RESOURCE_DESC& resourceDesc,
			D3D12_CLEAR_VALUE clearValue, D3D12_GPU_VIRTUAL_ADDRESS virtualAddress = D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN);
	
	protected:

		// ���ÿ�������ж��ٸ��ֽ�
		static size_t BytesPerPixel(DXGI_FORMAT format);

#pragma region ��Ҫ�Ƕ����ظ�ʽ��һЩת��������һЩ����
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