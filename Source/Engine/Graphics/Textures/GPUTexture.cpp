#include "GPUTexture.h"

using namespace DawnEngine;


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
