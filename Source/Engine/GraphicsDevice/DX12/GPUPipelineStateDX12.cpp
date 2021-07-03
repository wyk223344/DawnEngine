#if GRAPHICS_API_DIRECTX12

#include "GPUPipelineStateDX12.h"
#include "GPUResourceDX12.h"
#include "GPUDeviceDX12.h"
#include "GPUTextureDX12.h"
#include "d3dx12.h"
#include "IncludeDX12Headers.h"
#include "Engine/Graphics/PixelFormatExtensions.h"

using namespace DawnEngine::DX12;


ID3D12PipelineState* GPUPipelineStateDX12::GetState(GPUTextureDX12* depthHandle, GPUTextureDX12* rtHandle)
{
    GPUPipelineStateKeyDX12 key;
    key.RenderTargetFormat = rtHandle->Format();
    key.DepthFormat = depthHandle->Format();
    key.MSAA = rtHandle->MultiSampleLevel();

    auto iter = m_PSOCache.find(GetHash(key));
    if (iter != m_PSOCache.end())
    {
        return iter->second;
    }
    
    m_PipelineStateDescDX12.NumRenderTargets = 1;
    m_PipelineStateDescDX12.RTVFormats[0] = RenderToolsDX12::ToDxgiFormat(key.RenderTargetFormat);
    m_PipelineStateDescDX12.DSVFormat = RenderToolsDX12::ToDxgiFormat(PixelFormatExtensions::FindDepthStencilFormat(key.DepthFormat));
    m_PipelineStateDescDX12.SampleDesc.Count = 1;
    m_PipelineStateDescDX12.SampleDesc.Quality = 0;

    ID3D12PipelineState* state = nullptr;
    ThrowIfFailed(m_Device->GetDevice()->CreateGraphicsPipelineState(&m_PipelineStateDescDX12, IID_PPV_ARGS(&state)));
    m_PSOCache[GetHash(key)] = state;
    return state;
}


bool GPUPipelineStateDX12::OnInit()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psDesc;
	psDesc.pRootSignature = m_Device->GetRootSignature();
    psDesc.VS = { m_Desc.VS->GetBufferHandle(), m_Desc.VS->GetBufferSize() };
    psDesc.PS = { m_Desc.PS->GetBufferHandle(), m_Desc.PS->GetBufferSize() };
    psDesc.InputLayout = { static_cast<D3D12_INPUT_ELEMENT_DESC*>(m_Desc.VS->GetInputLayoutData()), m_Desc.VS->GetInputLayoutSize() };
    psDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psDesc.SampleMask = UINT_MAX;
    psDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    m_PipelineStateDescDX12 = psDesc;
    return true;
}

#endif