#if GRAPHICS_API_DIRECTX12

#include "GPUContextDX12.h"
#include "GPUDeviceDX12.h"
#include "GPUResourceDX12.h"
#include "GPUResourceStateDX12.h"
#include "GPUTextureDX12.h"
#include "GPUBufferDX12.h"
#include "GPUPipelineStateDX12.h"
#include "GPUConstantBufferDX12.h"
#include "UploadBufferDX12.h"
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
	m_RTDirtyFlag = false;
	m_PSDirtyFlag = false;
	m_CBDirtyFlag = false;
	m_SRDirtyMask = 0;
	m_RenderTargetTexture = nullptr;
	m_DepthTexture = nullptr;
	m_VertexBufferHandle = nullptr;
	m_IndexBufferHandle = nullptr;
	Platform::MemoryClear(&m_ConstantBufferHandles, sizeof(m_ConstantBufferHandles));
	Platform::MemoryClear(&m_ShaderResourceHandles, sizeof(m_ShaderResourceHandles));
	// 设置根签名
	m_CommandList->SetGraphicsRootSignature(m_Device->GetRootSignature());

	// TODO: RingHeap_CBV_SRV_UAV并没有使用
	ID3D12DescriptorHeap* heaps[] = { m_Device->RingHeap_CBV_SRV_UAV.GetHeap() };
	m_CommandList->SetDescriptorHeaps(ARRAY_COUNT(heaps), heaps);
}

void GPUContextDX12::SetResourceState(GPUResourceOwnerDX12* resource, D3D12_RESOURCE_STATES after, int32 subresourceIndex)
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

uint64 GPUContextDX12::Execute(bool waitForCompletion)
{
	auto queue = m_Device->GetGraphicsQueue();
	// 执行指令
	const uint64 fenceValue = queue->ExecuteCommandList(m_CommandList);
	// 释放对当前allocator的引用
	queue->DiscardAllocator(fenceValue, m_CurrentAllocator);
	m_CurrentAllocator = nullptr;
	// 等待GPU
	if (waitForCompletion)
	{
		queue->WaitForFence(fenceValue);
	}
	return fenceValue;
}

void GPUContextDX12::FrameBegin()
{
	GPUContext::FrameBegin();
	Reset();
}

void GPUContextDX12::FrameEnd()
{
	GPUContext::FrameEnd();
	Execute();
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

void GPUContextDX12::ClearDepth(GPUTexture* depthBuffer, float depthValue)
{
	auto depthBufferDX12 = static_cast<GPUTextureDX12*>(depthBuffer);

	if (depthBufferDX12)
	{
		SetResourceState(depthBufferDX12->GetResourceOwner(), D3D12_RESOURCE_STATE_DEPTH_WRITE);
		flushRBs();

		m_CommandList->ClearDepthStencilView(depthBufferDX12->DSV(), D3D12_CLEAR_FLAG_DEPTH, depthValue, 0xff, 0, nullptr);
	}
}

void GPUContextDX12::SetRenderTarget(GPUTexture* rt)
{
	GPUTextureDX12* rtDX12 = static_cast<GPUTextureDX12*>(rt);
	if (m_RenderTargetTexture != rtDX12 || m_DepthTexture != nullptr)
	{
		m_RTDirtyFlag = true;
		m_PSDirtyFlag = true;
		m_RenderTargetTexture = rtDX12;
		m_DepthTexture = nullptr;
	}
}

void GPUContextDX12::SetRenderTarget(GPUTexture* rt, GPUTexture* depthBuffer)
{
	GPUTextureDX12* rtDX12 = rt != nullptr ? static_cast<GPUTextureDX12*>(rt) : nullptr;
	auto depthBufferDX12 = depthBuffer ? static_cast<GPUTextureDX12*>(depthBuffer) : nullptr;
	if (m_RenderTargetTexture != rtDX12 || m_DepthTexture != depthBuffer)
	{
		m_RTDirtyFlag = true;
		m_PSDirtyFlag = true;
		m_RenderTargetTexture = rtDX12;
		m_DepthTexture = depthBufferDX12;
	}
}

void GPUContextDX12::BindSR(int32 slot, GPUTexture* texture)
{
	ASSERT(slot >= 0 && slot < DX12_MAX_SR_BINDED);
	const auto texDX12 = static_cast<GPUTextureDX12*>(texture);
	if (m_ShaderResourceHandles[slot] != texDX12)
	{
		m_SRDirtyMask |= 1 << slot;
		m_ShaderResourceHandles[slot] = texDX12;
	}
}

void GPUContextDX12::BindVB(GPUBuffer* vertexBuffer)
{
	const auto vbDX12 = static_cast<GPUBufferDX12*>(vertexBuffer);
	D3D12_VERTEX_BUFFER_VIEW view;
	vbDX12->GetVBView(view);
	if (m_VertexBufferHandle != vbDX12)
	{
		m_CommandList->IASetVertexBuffers(0, 1, &view);
		m_VertexBufferHandle = vbDX12;
	}
}

void GPUContextDX12::BindIB(GPUBuffer* indexBuffer)
{
	const auto ibDX12 = static_cast<GPUBufferDX12*>(indexBuffer);
	D3D12_INDEX_BUFFER_VIEW view;
	ibDX12->GetIBView(view);
	if (m_IndexBufferHandle != ibDX12)
	{
		m_CommandList->IASetIndexBuffer(&view);
		m_IndexBufferHandle = ibDX12;
	}
}

void GPUContextDX12::BindCB(int32 slot, GPUConstantBuffer* cb)
{
	assert(slot >= 0 && slot < DX12_MAX_CB_BINDED);
	auto cbDX12 = static_cast<GPUConstantBufferDX12*>(cb);
	if (m_ConstantBufferHandles[slot] != cbDX12)
	{
		m_CBDirtyFlag = true;
		m_ConstantBufferHandles[slot] = cbDX12;
	}
}

void GPUContextDX12::UpdateCB(GPUConstantBuffer* cb, const void* data)
{
	assert(data && cb);
	auto cbDX12 = static_cast<GPUConstantBufferDX12*>(cb);
	const uint32 size = cbDX12->GetSize();
	if (size == 0)
	{
		return;
	}
	DynamicAllocation allocation = m_Device->UploadBuffer->Allocate(size, D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT);
	Platform::MemoryCopy(allocation.CPUAddress, data, allocation.Size);
	cbDX12->GPUAddress = allocation.GPUAddress;
	for (uint32 i = 0; i < ARRAY_COUNT(m_ConstantBufferHandles); i++)
	{
		if (m_ConstantBufferHandles[i] == cbDX12)
		{
			m_CBDirtyFlag = true;
			break;
		}
	}
}

void GPUContextDX12::UpdateBuffer(GPUBuffer* buffer, const void* data, uint32 size, uint32 offset)
{
	GPUBufferDX12* bufferDX12 = static_cast<GPUBufferDX12*>(buffer);
	SetResourceState(bufferDX12, D3D12_RESOURCE_STATE_COPY_DEST);
	flushRBs();
	m_Device->UploadBuffer->UploadBuffer(this, bufferDX12->GetResource(), offset, data, size);
}

void GPUContextDX12::UpdateTexture(GPUTexture* texture, int32 arrayIndex, int32 mipIndex, const void* data, uint32 rowPitch, uint32 slicePitch)
{
	auto textureDX12 = static_cast<GPUTextureDX12*>(texture);

	SetResourceState(textureDX12, D3D12_RESOURCE_STATE_COPY_DEST);
	flushRBs();

	m_Device->UploadBuffer->UploadTexture(this, textureDX12->GetResource(), data, rowPitch, slicePitch, mipIndex, arrayIndex);
}

void GPUContextDX12::DrawIndexedInstanced(uint32 indicesCount, uint32 instanceCount, int32 startIndex, int32 startVertex, int32 startInstance)
{
	onDrawCall();
	m_CommandList->DrawIndexedInstanced(indicesCount, instanceCount, startIndex, startVertex, startInstance);
}

void GPUContextDX12::SetState(GPUPipelineState* state)
{
	if (m_CurrentState != state)
	{
		m_CurrentState = static_cast<GPUPipelineStateDX12*>(state);
		m_PSDirtyFlag = true;
	}
	
}

GPUPipelineState* GPUContextDX12::GetState() const
{
	return nullptr;
}

void GPUContextDX12::ClearState()
{

}

void GPUContextDX12::FlushState()
{
	flushRTVs();
	flushRBs();
}

void GPUContextDX12::Flush()
{
	if (!m_CurrentAllocator)
	{
		return;
	}
	Execute();
	Reset();
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

void GPUContextDX12::onDrawCall()
{
	flushSRVs();
	flushRTVs();
	flushRBs();
	flushPS();
	flushCBs();
}

void GPUContextDX12::flushSRVs()
{
	if (m_SRDirtyMask == 0) { return; }

	const uint32 srCount = Math::FloorLog2(m_SRDirtyMask) + 1;

	D3D12_CPU_DESCRIPTOR_HANDLE srcDescriptorRangeStarts[DX12_MAX_SR_BINDED];

	for (uint32 i = 0; i < srCount; i++)
	{
		const auto handle = m_ShaderResourceHandles[i];
		if (handle != nullptr)
		{
			srcDescriptorRangeStarts[i] = handle->SRV();
			D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

			SetResourceState(handle->GetResourceOwner(), state);
		}
		else
		{
			srcDescriptorRangeStarts[i] = m_Device->Null_SRV.CPU();
		}
	}

	auto allocation = m_Device->RingHeap_CBV_SRV_UAV.AllocateTable(srCount);
	allocation.CPU;
	m_Device->GetDevice()->CopyDescriptors(
		1,
		&allocation.CPU,
		&srCount,
		srCount,
		srcDescriptorRangeStarts,
		nullptr,
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
	);

	m_CommandList->SetGraphicsRootDescriptorTable(3, allocation.GPU);
}

void GPUContextDX12::flushRTVs()
{
	if (m_RTDirtyFlag)
	{
		m_RTDirtyFlag = false;
		// Render Target
		D3D12_CPU_DESCRIPTOR_HANDLE renderTargetCPU;
		if (m_RenderTargetTexture)
		{
			renderTargetCPU = m_RenderTargetTexture->RTV();
			SetResourceState(m_RenderTargetTexture, D3D12_RESOURCE_STATE_RENDER_TARGET);
		}
		else
		{
			renderTargetCPU.ptr = 0;
		}
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
		m_CommandList->OMSetRenderTargets(1, renderTargetCPU.ptr != 0 ? &renderTargetCPU : nullptr, true, depthBufferCPU.ptr != 0 ? &depthBufferCPU : nullptr);
	}
}

void GPUContextDX12::flushUAVs()
{

}

void GPUContextDX12::flushCBs()
{
	if (m_CBDirtyFlag)
	{
		m_CBDirtyFlag = false;
		for (uint32 i = 0; i < ARRAY_COUNT(m_ConstantBufferHandles); i++)
		{
			auto cb = m_ConstantBufferHandles[i];
			if (cb)
			{
				assert(cb->GPUAddress != 0);
				m_CommandList->SetGraphicsRootConstantBufferView(i, cb->GPUAddress);
			}
		}
	}
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
	if (m_PSDirtyFlag && m_CurrentState)
	{
		m_PSDirtyFlag = false;

		m_CommandList->SetPipelineState(m_CurrentState->GetState(m_DepthTexture, m_RenderTargetTexture));
		m_CommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}

#endif