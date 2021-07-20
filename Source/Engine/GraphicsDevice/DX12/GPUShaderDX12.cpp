#if GRAPHICS_API_DIRECTX12

#include "Engine/Graphics/Enums.h"
#include "GPUShaderDX12.h"
#include "GPUShaderProgramDX12.h"

using namespace DawnEngine;
using namespace DawnEngine::DX12;


GPUShaderProgram* GPUShaderDX12::CreateShaderProgram(ShaderStage stage, const void* binary, uint64 size)
{
    GPUShaderProgram* shader = nullptr;
    switch (stage)
    {
    case ShaderStage::Vertex:
    {
        shader = New<GPUShaderProgramVSDX12>();
        break;
    }
    case ShaderStage::Pixel:
    {
        shader = New<GPUShaderProgramPSDX12>();
        break;
    }
    }
    shader->Init(binary, size);
    m_ShaderDict[stage] = shader;
    return shader;
}


#endif