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
			// 是否开启深度写入
			bool DepthWriteEnable;

			// 是否开启深度测试
			bool DepthTestEnable;

			// 是否开启深度Clip
			bool DepthClipEnable;

			// 深度比较方法
			ComparisonFunc DepthFunc;

			// vertex shader
			GPUShaderProgramVS* VS;

			// pixel shader
			GPUShaderProgramPS* PS;

			// 是否启用线框模式
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