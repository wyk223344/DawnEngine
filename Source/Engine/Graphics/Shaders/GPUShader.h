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
		virtual GPUShaderProgram* CreateShaderProgram(ShaderStage stage, std::string filePath) = 0;

	public:

		GPUShaderProgramVS* CreateShaderProgramVS(std::string filePath)
		{
			return static_cast<GPUShaderProgramVS*>(CreateShaderProgram(ShaderStage::Vertex, filePath));
		}

		GPUShaderProgramPS* CreateShaderProgramPS(std::string filePath)
		{
			return static_cast<GPUShaderProgramPS*>(CreateShaderProgram(ShaderStage::Pixel, filePath));
		}

	protected:

		std::map<ShaderStage, GPUShaderProgram*> m_ShaderDict;
	};
}