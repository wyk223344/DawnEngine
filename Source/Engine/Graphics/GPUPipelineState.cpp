#include "GPUPipelineState.h"

using namespace DawnEngine;


GPUPipelineState::Description GPUPipelineState::Description::Default =
{
    // Enable/disable depth write
    true,
    // Enable/disable depth test
    true,
    // DepthClipEnable
    false,
    // DepthFunc
    ComparisonFunc::Less,
    // Vertex shader
    nullptr,
    // Pixel shader
    nullptr,
    // True if use wireframe rendering
    false,
    // Primitives culling mode
    CullMode::Normal,
    // DepthBias
    0,
    // DepthBiasClamp
    0.0f,
    // SlopeScaledDepthBias
    0.0f,
};


GPUPipelineState::Description GPUPipelineState::Description::DefaultFullscreenTriangle =
{
    // Enable/disable depth write
    false,
    // Enable/disable depth test
    false,
    // DepthClipEnable
    false,
    // DepthFunc
    ComparisonFunc::Less,
    // Vertex shader
    nullptr,
    // Pixel shader
    nullptr,
    // True if use wireframe rendering
    false,
    // Primitives culling mode
    CullMode::TwoSided,
    // DepthBias
    0,
    // DepthBiasClamp
    0.0f,
    // SlopeScaledDepthBias
    0.0f,
};


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