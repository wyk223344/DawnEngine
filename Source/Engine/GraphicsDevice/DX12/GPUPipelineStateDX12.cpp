#if GRAPHICS_API_DIRECTX12

#include "GPUPipelineStateDX12.h"
#include "GPUResourceDX12.h"
#include "GPUDeviceDX12.h"
#include "GPUTextureDX12.h"
#include "d3dx12.h"
#include "IncludeDX12Headers.h"
#include "Engine/Graphics/PixelFormatExtensions.h"

using namespace DawnEngine::DX12;


ID3D12PipelineState* GPUPipelineStateDX12::GetState(GPUTextureViewDX12* depthHandle, GPUTextureViewDX12* rtHandle)
{
    GPUPipelineStateKeyDX12 key;
    key.RenderTargetFormat = rtHandle ? rtHandle->GetFormat() : PixelFormat::Unknown;
    key.DepthFormat = depthHandle ? depthHandle->GetFormat() : PixelFormat::Unknown;
    key.MSAA = rtHandle ? rtHandle->GetMSAA() : MSAALevel::None;

    uint32 hashKey = GetHash(key);
    auto iter = m_PSOCache.find(hashKey);
    if (iter != m_PSOCache.end())
    {
        return iter->second;
    }
    
    m_PipelineStateDescDX12.NumRenderTargets = rtHandle ? 1 : 0;
    m_PipelineStateDescDX12.RTVFormats[0] = RenderToolsDX12::ToDxgiFormat(key.RenderTargetFormat);
    m_PipelineStateDescDX12.DSVFormat = RenderToolsDX12::ToDxgiFormat(key.DepthFormat);
    m_PipelineStateDescDX12.SampleDesc.Count = 1;
    m_PipelineStateDescDX12.SampleDesc.Quality = 0;

    ID3D12PipelineState* state = nullptr;
    ThrowIfFailed(m_Device->GetDevice()->CreateGraphicsPipelineState(&m_PipelineStateDescDX12, IID_PPV_ARGS(&state)));
    m_PSOCache[hashKey] = state;
    return state;
}


bool GPUPipelineStateDX12::OnInit()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psDesc;
    Platform::MemoryClear(&psDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psDesc.pRootSignature = m_Device->GetRootSignature();
    psDesc.VS = { m_Desc.VS->GetBufferHandle(), m_Desc.VS->GetBufferSize() };
    psDesc.PS = { m_Desc.PS->GetBufferHandle(), m_Desc.PS->GetBufferSize() };
    psDesc.InputLayout = { static_cast<D3D12_INPUT_ELEMENT_DESC*>(m_Desc.VS->GetInputLayoutData()), m_Desc.VS->GetInputLayoutSize() };
    psDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psDesc.RasterizerState.CullMode = m_Desc.CullMode == CullMode::Normal ? D3D12_CULL_MODE_BACK : 
        ( m_Desc.CullMode == CullMode::Inverted ? D3D12_CULL_MODE_FRONT : D3D12_CULL_MODE_NONE );
    psDesc.RasterizerState.FillMode = m_Desc.Wireframe ? D3D12_FILL_MODE_WIREFRAME : D3D12_FILL_MODE_SOLID;
    psDesc.RasterizerState.DepthBias = m_Desc.DepthBias;
    psDesc.RasterizerState.DepthBiasClamp = m_Desc.DepthBiasClamp;
    psDesc.RasterizerState.SlopeScaledDepthBias = m_Desc.SlopeScaledDepthBias;
    psDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psDesc.DepthStencilState.DepthEnable = m_Desc.DepthTestEnable;
    psDesc.DepthStencilState.DepthWriteMask = m_Desc.DepthWriteEnable ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;
    psDesc.DepthStencilState.DepthFunc = static_cast<D3D12_COMPARISON_FUNC>(m_Desc.DepthFunc);
    psDesc.SampleMask = UINT_MAX;
    psDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    m_PipelineStateDescDX12 = psDesc;
    return true;
}

#endif