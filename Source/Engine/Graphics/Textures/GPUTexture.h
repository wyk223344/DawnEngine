#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Graphics/Enums.h"
#include "Engine/Graphics/GPUResource.h"
#include "Engine/Graphics/PixelFormat.h"
#include "GPUTextureDescription.h"

namespace DawnEngine
{
	//class GPUTextureView : GPUResourceView
	//{
	//public:

	//	GPUResource* GetParent() const { return m_Parent; }

	//	PixelFormat GetFormat() const { return m_Format; }

	//	MSAALevel GetMSAA() const { return m_Msaa; }

	//protected:

	//	void Init(GPUResource* parent, PixelFormat format, MSAALevel msaa)
	//	{
	//		m_Parent = parent;
	//		m_Format = format;
	//		m_Msaa = msaa;
	//	}

	//protected:

	//	GPUResource* m_Parent = nullptr;
	//	PixelFormat m_Format = PixelFormat::Unknown;
	//	MSAALevel m_Msaa = MSAALevel::None;
	//};

	class GPUTexture : GPUResource
	{
	public:

		GPUTexture();

	public:

		int32 Width() const { return m_Desc.Width; }

		int32 Height() const { return m_Desc.Height; }

		int32 Depth() const { return m_Desc.Depth; }

		PixelFormat Format() const { return m_Desc.Format; }

		MSAALevel MultiSampleLevel() const { return m_Desc.MultiSampleLevel; }

	public:

		bool Init(const GPUTextureDescription& desc);

	protected:

		virtual bool OnInit() = 0;

	protected:

		GPUTextureDescription m_Desc;
	};
}