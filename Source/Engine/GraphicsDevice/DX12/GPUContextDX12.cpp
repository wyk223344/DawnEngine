#if GRAPHICS_API_DIRECTX12

#include "GPUContextDX12.h"
#include "GPUDeviceDX12.h"
#include "GPUResourceDX12.h"
#include "GPUResourceStateDX12.h"
#include "GPUTextureDX12.h"
#include "CommandQueueDX12.h"
#include "Engine/Engine/Engine.h"
#include "GPUSwapChainDX12.h"
#include "IncludeDX12Headers.h"
#include "Engine/Core/Include.h"

using namespace DawnEngine;
using namespace DawnEngine::DX12;


GPUContextDX12::GPUContextDX12(GPUDeviceDX12* device, D3D12_COMMAND_LIST_TYPE type)
	: m_Device(device)
	, m_CommandList(nullptr)
	, m_CurrentAllocator(nullptr)
	, m_ResourceBarrierNum(0)
{
	m_CurrentAllocator = device->GetGraphicsQueue()->RequestAllocator();
	ThrowIfFailed(device->GetDevice()->CreateCommandList(0, type, m_CurrentAllocator, nullptr, IID_PPV_ARGS(&m_CommandList)));

}

GPUContextDX12::~GPUContextDX12()
{
	if (m_CommandList)
	{
		m_CommandList->Release();
	}
}

void GPUContextDX12::Reset()
{
	if (m_CurrentAllocator == nullptr)
	{
		m_CurrentAllocator = m_Device->GetGraphicsQueue()->RequestAllocator();
		m_CommandList->Reset(m_CurrentAllocator, nullptr);
	}
}

void GPUContextDX12::SetResourceState(GPUResourceOwnerDX12* resource, D3D12_RESOURCE_STATES after, int32 subresourceIndex = -1)
{
	auto nativeResource = resource->GetResource();
	if (nativeResource == nullptr)
	{
		return;
	}
	auto& state = resource->State;
	const D3D12_RESOURCE_STATES before = state.GetState();
	if (GPUResourceStateDX12::IsTransitionNeeded(before, after))
	{
		addResourceBarrier(resource->GetResource(), before, after);
	}
}

void GPUContextDX12::FrameBegin()
{
	GPUContext::FrameBegin();
	Reset();
}

void GPUContextDX12::FrameEnd()
{
	// TODO: temp
	DawnEngine::Window* window = DawnEngine::Engine::MainWindow;
	// auto temp = static_cast<GPUSwapChainDX12*>(window->GetSwapChain());
	auto swapChain = static_cast<GPUSwapChainDX12*>(window->GetSwapChain());
	ID3D12Resource* resource = swapChain->m_SwapChainBuffers[swapChain->m_CurrentFrameIndex].Get();
	auto slot = &swapChain->m_SwapChainSlots[swapChain->m_CurrentFrameIndex];
	addResourceBarrier(resource, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	flushRBs();

	D3D12_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(800);
	viewport.Height = static_cast<float>(600);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_CommandList->RSSetViewports(1, &viewport);

	D3D12_RECT rect = { 0, 0, 800, 600 };
	m_CommandList->RSSetScissorRects(1, &rect);

	// Clear the back buffer and depth buffer.
	m_CommandList->ClearRenderTargetView(slot->CPU(), Color::Blue.Raw, 0, nullptr);

	// Specify the buffers we are going to render to.
	m_CommandList->OMSetRenderTargets(1, &slot->CPU(), true, nullptr);

	addResourceBarrier(resource, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	flushRBs();

	GPUContext::FrameEnd();
	auto queue = m_Device->GetGraphicsQueue();
	// 执行指令
	const uint64 fenceValue = queue->ExecuteCommandList(m_CommandList);
	// 释放对当前allocator的引用
	queue->DiscardAllocator(fenceValue, m_CurrentAllocator);
	m_CurrentAllocator = nullptr;

	swapChain->Present(false);
}

void GPUContextDX12::SetViewport(const Math::Viewport& viewport)
{
	m_CommandList->RSSetViewports(1, (D3D12_VIEWPORT*)&viewport);
}

void GPUContextDX12::SetScissor(const Math::Rectangle& scissorRect)
{
	D3D12_RECT rect;
	rect.left = (LONG)scissorRect.GetLeft();
	rect.right = (LONG)scissorRect.GetRight();
	rect.top = (LONG)scissorRect.GetTop();
	rect.bottom = (LONG)scissorRect.GetBottom();
	m_CommandList->RSSetScissorRects(1, &rect);
}

void GPUContextDX12::Clear(GPUTexture* rt, const Color& color)
{
	auto rtDX12 = static_cast<GPUTextureDX12*>(rt);
	if (rtDX12)
	{
		SetResourceState(rtDX12, D3D12_RESOURCE_STATE_RENDER_TARGET);
		flushRBs();
		m_CommandList->ClearRenderTargetView(rtDX12->RTV(), color.Raw, 0, nullptr);
	}
}

void GPUContextDX12::SetRenderTarget(GPUTexture* rt)
{
	GPUTextureDX12* rtDX12 = static_cast<GPUTextureDX12*>(rt);
	if (m_RenderTargetTexture != rtDX12 || m_DepthTexture != nullptr)
	{
		m_RTDirtyFlag = true;
		m_RenderTargetTexture = rtDX12;
		m_DepthTexture = nullptr;
	}
}

void GPUContextDX12::SetRenderTarget(GPUTexture* rt, GPUTexture* depthBuffer)
{
	GPUTextureDX12* rtDX12 = static_cast<GPUTextureDX12*>(rt);
	auto depthBufferDX12 = static_cast<GPUTextureDX12*>(depthBuffer);
	if (m_RenderTargetTexture != rtDX12 || m_DepthTexture != depthBuffer)
	{
		m_RTDirtyFlag = true;
		m_RenderTargetTexture = rtDX12;
		m_DepthTexture = depthBufferDX12;
	}
}

void GPUContextDX12::BindVB(GPUBuffer* vertexBuffer)
{

}

void GPUContextDX12::BindIB(GPUBuffer* indexBuffer)
{

}

void GPUContextDX12::DrawIndexedInstanced(uint32 indicesCount, uint32 instanceCount, int32 startIndex = 0, int32 startVertex = 0, int32 startInstance = 0)
{

}

void GPUContextDX12::SetState(GPUPipelineState* state)
{

}

GPUPipelineState* GPUContextDX12::GetState() const
{

}

void GPUContextDX12::ClearState()
{

}

void GPUContextDX12::FlushState()
{

}

void GPUContextDX12::Flush()
{

}

void GPUContextDX12::addResourceBarrier(ID3D12Resource* resource, const D3D12_RESOURCE_STATES before, const D3D12_RESOURCE_STATES after)
{
	D3D12_RESOURCE_BARRIER& barrier = m_ResourceBarrierBuffers[m_ResourceBarrierNum];
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = resource;
	barrier.Transition.StateBefore = before;
	barrier.Transition.StateAfter = after;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	m_ResourceBarrierNum++;
}

void GPUContextDX12::flushSRVs()
{

}

void GPUContextDX12::flushRTVs()
{
	if (m_RTDirtyFlag)
	{
		m_RTDirtyFlag = false;
		// Render Target
		D3D12_CPU_DESCRIPTOR_HANDLE renderTargetCPU = m_RenderTargetTexture->RTV();
		SetResourceState(m_RenderTargetTexture, D3D12_RESOURCE_STATE_RENDER_TARGET);
		// Depth Buffer
		D3D12_CPU_DESCRIPTOR_HANDLE depthBufferCPU;
		if (m_DepthTexture)
		{
			depthBufferCPU = m_DepthTexture->DSV();
			SetResourceState(m_DepthTexture, D3D12_RESOURCE_STATE_DEPTH_WRITE);
		}
		else
		{
			depthBufferCPU.ptr = 0;
		}
		// Sumbit command
		m_CommandList->OMSetRenderTargets(1, &renderTargetCPU, true, depthBufferCPU.ptr != 0 ? &depthBufferCPU : nullptr);
	}
}

void GPUContextDX12::flushUAVs()
{

}

void GPUContextDX12::flushCBs()
{

}

void GPUContextDX12::flushRBs()
{
	if (m_ResourceBarrierNum > 0)
	{
		m_CommandList->ResourceBarrier(m_ResourceBarrierNum, m_ResourceBarrierBuffers);
		m_ResourceBarrierNum = 0;
	}
}

void GPUContextDX12::flushPS()
{

}

#endif