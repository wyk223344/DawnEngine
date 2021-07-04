#pragma once
#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/Shaders/GPUShader.h"
#include "GPUResourceDX12.h"

namespace DawnEngine::DX12
{
	class GPUShaderDX12 : public GPUResourceDX12<GPUShader>
	{
	public:

		GPUShaderDX12(GPUDeviceDX12* device)
			: GPUResourceDX12<GPUShader>(device)
		{
		}

	public:
		GPUShaderProgram* CreateShaderProgram(ShaderStage stage, std::string filePath) override;
	};

}

#endif