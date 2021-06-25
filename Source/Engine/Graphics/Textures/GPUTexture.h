#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Graphics/Enums.h"
#include "Engine/Graphics/GPUResource.h"
#include "Engine/Graphics/PixelFormat.h"
#include "GPUTextureDescription.h"

namespace DawnEngine
{
	class GPUTextureView : GPUResourceView
	{
	public:

		GPUResource* GetParent() const { return m_Parent; }

		PixelFormat GetFormat() const { return m_Format; }

		MSAALevel GetMSAA() const { return m_Msaa; }

	protected:

		void Init(GPUResource* parent, PixelFormat format, MSAALevel msaa)
		{
			m_Parent = parent;
			m_Format = format;
			m_Msaa = msaa;
		}

	protected:

		GPUResource* m_Parent = nullptr;
		PixelFormat m_Format = PixelFormat::Unknown;
		MSAALevel m_Msaa = MSAALevel::None;
	};

	class GPUTexture : GPUResource
	{
	public:

		GPUTexture()
		{
		}

		virtual GPUTextureView* View() const = 0;

	public:

		int32 Width() const { return m_Desc.Width; }

		int32 Height() const { return m_Desc.Height; }

		int32 Depth() const { return m_Desc.Depth; }

	protected:

		GPUTextureDescription m_Desc;
	};
}