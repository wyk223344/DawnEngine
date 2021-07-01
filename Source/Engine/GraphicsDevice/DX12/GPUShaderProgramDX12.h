#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/Shaders/GPUShaderProgram.h"
#include "IncludeDX12Headers.h"


namespace DawnEngine::DX12
{
	template<typename BaseType>
	class GPUShaderProgramDX12 : public BaseType
	{

	};

	class GPUShaderProgramVSDX12 : public GPUShaderProgramDX12<GPUShaderProgramVS>
	{

	};

	class GPUShaderProgramPSDX12 : public GPUShaderProgramDX12<GPUShaderProgramPS>
	{

	};
	
}

#endif