#pragma once

#include <map>


namespace DawnEngine
{
	class GPUContext;
	class GPUShader;
	class GPUPipelineState;
	class GPUConstantBuffer;
	class GPUTexture;
	class TextureData;

	class MaterialBase
	{
	public:

		virtual bool InitGPUResource() = 0;

		virtual void Draw(GPUContext* context) = 0;

	protected:



	protected:

		bool m_CBDirtyFlag = true;

		GPUShader* m_Shader;
		GPUPipelineState* m_PipelineState;
		GPUConstantBuffer* m_ConstantBuffer;
		
		// 待上传的纹理
		std::map<GPUTexture*, TextureData*> m_ReadyUpdateTexture;
	};
}