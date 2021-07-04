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

		virtual bool Init(std::string filePath) = 0;

		// ��ȡshader�׶�����
		virtual ShaderStage GetStage() const = 0;

		// ��ȡshader����
		virtual void* GetBufferHandle() const = 0;

		// ��ȡshader���ݳ���
		virtual uint32 GetBufferSize() const = 0;

	private:

		std::string m_Name;
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