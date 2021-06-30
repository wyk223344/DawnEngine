#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Graphics/GPUResource.h"
#include "Engine/Graphics/Enums.h"
#include <map>

namespace DawnEngine
{
	class GPUShaderProgram;

	class GPUShader : GPUResource
	{
	public:



	private:

		std::map<ShaderStage, GPUShaderProgram*> m_ShaderDict;
	};
}