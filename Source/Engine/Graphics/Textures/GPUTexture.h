#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Graphics/Enums.h"
#include "Engine/Graphics/GPUResource.h"
#include "Engine/Graphics/PixelFormat.h"
#include "GPUTextureDescription.h"

namespace DawnEngine
{
	class GPUTexture;

	class GPUTextureView : GPUResourceView
	{
	public:

		GPUTexture* GetParent() const;

		PixelFormat GetFormat() const;

		MSAALevel GetMSAA() const;

	protected:

		void Init(GPUTexture* parent)
		{
			m_Parent = parent;
		}

	protected:

		GPUTexture* m_Parent = nullptr;
	};

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

		GPUTextureView* View() const { return View(0); }

		virtual GPUTextureView* View(int32 arrayOrDepthIndex) const = 0;

		// virtual GPUTextureView* View(int32 arrayOrDepthIndex, int32 mipMapIndex) const = 0;

		virtual GPUTextureView* ViewArray() const = 0;

	public:

		bool Init(const GPUTextureDescription& desc);

	protected:

		virtual bool OnInit() = 0;

	protected:

		GPUTextureDescription m_Desc;
	};
}