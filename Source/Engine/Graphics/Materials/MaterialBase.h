#pragma once


namespace DawnEngine
{
	class GPUContext;
	class GPUShader;
	class GPUPipelineState;
	class GPUConstantBuffer;

	class MaterialBase
	{
	public:

		virtual bool InitGPUResource() = 0;

		virtual void Draw(GPUContext* context) = 0;

	protected:

		GPUShader* m_Shader;
		GPUPipelineState* m_PipelineState;
		GPUConstantBuffer* m_ConstantBuffer;
	};
}