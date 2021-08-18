#include "GPUTexture.h"

using namespace DawnEngine;

#pragma region GPUTextureView

GPUTexture* GPUTextureView::GetParent() const
{
	return m_Parent;
}

PixelFormat GPUTextureView::GetFormat() const
{
	return m_Parent->Format();
}

MSAALevel GPUTextureView::GetMSAA() const
{
	return m_Parent->MultiSampleLevel();
}

#pragma endregion

#pragma region GPUTexture

GPUTexture::GPUTexture()
{
	m_Desc.Clear();
}

bool GPUTexture::Init(const GPUTextureDescription& desc)
{
	ReleaseGPU();
	m_Desc = desc;
	if (!OnInit())
	{
		ReleaseGPU();
		return false;
	}
	return true;
}

#pragma endregion