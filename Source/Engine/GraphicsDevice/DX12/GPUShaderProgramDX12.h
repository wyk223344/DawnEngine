#pragma once

#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/Shaders/GPUShaderProgram.h"
#include "IncludeDX12Headers.h"
#include <string>

namespace DawnEngine::DX12
{
	template<typename BaseType>
	class GPUShaderProgramDX12 : public BaseType
	{
	};

	class GPUShaderProgramVSDX12 : public GPUShaderProgramDX12<GPUShaderProgramVS>
	{
	public:

		void* GetInputLayoutData() const override { return InputLayoutDX12::DefaultLayout; }

		byte GetInputLayoutSize() const override { return _countof(InputLayoutDX12::DefaultLayout); }
	};

	class GPUShaderProgramPSDX12 : public GPUShaderProgramDX12<GPUShaderProgramPS>
	{
	public:
	};
	
}

#endif