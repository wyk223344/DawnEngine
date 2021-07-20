#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Graphics/GPUResource.h"
#include "Engine/Graphics/Enums.h"
#include "GPUShaderProgram.h"
#include <map>
#include <string>

namespace DawnEngine
{

	class GPUShader : GPUResource
	{
	public:

		// ´´½¨shader³ÌÐò
		virtual GPUShaderProgram* CreateShaderProgram(ShaderStage stage, const void* binary, uint64 size) = 0;

	public:

		GPUShaderProgramVS* CreateShaderProgramVS(const void* binary, uint64 size)
		{
			return static_cast<GPUShaderProgramVS*>(CreateShaderProgram(ShaderStage::Vertex, binary, size));
		}

		GPUShaderProgramPS* CreateShaderProgramPS(const void* binary, uint64 size)
		{
			return static_cast<GPUShaderProgramPS*>(CreateShaderProgram(ShaderStage::Pixel, binary, size));
		}

	protected:

		std::map<ShaderStage, GPUShaderProgram*> m_ShaderDict;
	};
}