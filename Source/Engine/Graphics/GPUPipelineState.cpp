#include "GPUPipelineState.h"

using namespace DawnEngine;


bool GPUPipelineState::Init(Description& desc)
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