#pragma once

#include "Engine/Core/Include.h"
#include "GPUResource.h"
#include "Enums.h"
#include "Shaders/GPUShaderProgram.h"

namespace DawnEngine
{
	class GPUPipelineState : GPUResource
	{
	public:

		struct Description
		{
			// �Ƿ������д��
			bool DepthWriteEnable;

			// �Ƿ�����Ȳ���
			bool DepthTestEnable;

			// �Ƿ������Clip
			bool DepthClipEnable;

			// ��ȱȽϷ���
			ComparisonFunc DepthFunc;

			// vertex shader
			GPUShaderProgramVS* VS;

			// pixel shader
			GPUShaderProgramPS* PS;

			// �Ƿ������߿�ģʽ
			bool Wireframe;

			// cull mode
			CullMode CullMode;

		public:

			static Description Default;

			static Description DefaultFullscreenTriangle;
		};

	public:

		GPUPipelineState()
		{
		}

		bool Init(Description& desc);

	protected:

		virtual bool OnInit() = 0;

	protected:

		Description m_Desc;
	};
}