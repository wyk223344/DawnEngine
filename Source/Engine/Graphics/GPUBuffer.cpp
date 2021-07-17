#include "GPUBuffer.h"

using namespace DawnEngine;


bool GPUBuffer::Init(const GPUBufferDescription& desc)
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

void GPUBuffer::OnReleaseGPU()
{
}