#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Graphics/Enums.h"

#include <string>

namespace DawnEngine
{
	// ����shader�׶εķ�װ
	class GPUShaderProgram : Object
	{
	public:

		GPUShaderProgram()
			: m_ShaderBinary(nullptr)
			, m_Size(0)
		{
		}

		// ��ʼ��
		bool Init(const void* binary, uint64 size)
		{
			m_ShaderBinary = const_cast<void*>(binary);
			m_Size = size;
			return true;
		}

		// ��ȡshader����
		void* GetBufferHandle() const
		{
			return m_ShaderBinary;
		}

		// ��ȡshader���ݳ���
		uint64 GetBufferSize() const
		{
			return m_Size;
		}

	public:

		// ��ȡshader�׶�����
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

		// ��ȡ���벼��
		virtual void* GetInputLayoutData() const = 0;

		// ��ȡ���벼�ֵĴ�С
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