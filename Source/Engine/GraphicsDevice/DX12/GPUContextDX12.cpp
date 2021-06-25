#if GRAPHICS_API_DIRECTX12

#include "GPUContextDX12.h"
#include "GPUDeviceDX12.h"
#include "CommandQueueDX12.h"
#include "Engine/Engine/Engine.h"
#include "GPUSwapChainDX12.h"

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
	flushResourceBarriers();

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
	flushResourceBarriers();

	GPUContext::FrameEnd();
	auto queue = m_Device->GetGraphicsQueue();
	// 执行指令
	const uint64 fenceValue = queue->ExecuteCommandList(m_CommandList);
	// 释放对当前allocator的引用
	queue->DiscardAllocator(fenceValue, m_CurrentAllocator);
	m_CurrentAllocator = nullptr;

	swapChain->Present(false);
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

void GPUContextDX12::flushResourceBarriers()
{
	if (m_ResourceBarrierNum > 0)
	{
		m_CommandList->ResourceBarrier(m_ResourceBarrierNum, m_ResourceBarrierBuffers);
		m_ResourceBarrierNum = 0;
	}
}

#endif