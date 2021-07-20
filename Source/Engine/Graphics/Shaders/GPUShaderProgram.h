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

		GPUShaderProgram()
			: m_ShaderBinary(nullptr)
			, m_Size(0)
		{
		}

		// 初始化
		bool Init(const void* binary, uint64 size)
		{
			m_ShaderBinary = const_cast<void*>(binary);
			m_Size = size;
			return true;
		}

		// 获取shader数据
		void* GetBufferHandle() const
		{
			return m_ShaderBinary;
		}

		// 获取shader数据长度
		uint64 GetBufferSize() const
		{
			return m_Size;
		}

	public:

		// 获取shader阶段类型
		virtual ShaderStage GetStage() const = 0;

	protected:

		std::string m_Name;

		void* m_ShaderBinary;
		uint64 m_Size;
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