#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Graphics/Enums.h"

#include <string>

namespace DawnEngine
{
	// 单个shader阶段的封装
	class GPUShaderProgram : Object
	{
	public:

		virtual bool Init(std::string filePath) = 0;

		// 获取shader阶段类型
		virtual ShaderStage GetStage() const = 0;

		// 获取shader数据
		virtual void* GetBufferHandle() const = 0;

		// 获取shader数据长度
		virtual uint32 GetBufferSize() const = 0;

	private:

		std::string m_Name;
	};

	// vertex shader
	class GPUShaderProgramVS : public GPUShaderProgram
	{
	public:

		// 获取输入布局
		virtual void* GetInputLayoutData() const = 0;

		// 获取输入布局的大小
		virtual byte GetInputLayoutSize() const = 0;

	public:

		ShaderStage GetStage() const override { return ShaderStage::Vertex; }
	};

	// pixel shader
	class GPUShaderProgramPS : public GPUShaderProgram
	{
	public:

		ShaderStage GetStage() const override { return ShaderStage::Pixel; }
	};
}