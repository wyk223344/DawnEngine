#pragma once

#if GRAPHICS_API_DIRECTX12

#include "IncludeDX12Headers.h"
#include "Engine/Graphics/GPUContext.h"
#include "Engine/Core/Include.h"

/*
	DX12执行命令流程:
	1. 假设已经有了ID3D12Device

	2. 生成一个围栏ID3D12Fence
		ID3D12Device->CreateFence

	3. 创建针对该设备的命令队列: ID3D12CommandQueue
		ID3D12Device->CreateCommandQueue

	4. 创建一个命令分配器:ID3D12CommandAllocator（对应你所要执行的命令类型）
		ID3D12Device->CreateCommandAllocator

	5. 使用该命令分配器生成一个命令列表: ID3D12CommandList
		ID3D12Device->CreateCommandList

	6. 向命令列表中插入命令
		ID3D12CommandList->xxx		// 插入命令
		ID3D12CommandList->xxx		// 插入命令
		ID3D12CommandList->close(); // 关闭

	7. 发送给GPU执行命令
		ID3D12CommandQueue->ExecuteCommandLists

	8. 插入围栏值
		ID3D12CommandQueue-Signal

	9. 其他操作，交换缓冲区等，不属于这里的功能
*/



namespace DawnEngine::DX12
{
	class GPUDeviceDX12;
	class GPUTextureDX12;
	class GPUTextureViewDX12;
	class GPUPipelineStateDX12;
	class GPUResourceOwnerDX12;
	class GPUConstantBufferDX12;
	class GPUBufferDX12;
	class IShaderResourceDX12;

	class GPUContextDX12 : GPUContext
	{
	public:

		GPUContextDX12(GPUDeviceDX12* device, D3D12_COMMAND_LIST_TYPE type);

		~GPUContextDX12();

	public:

		// 重置CommandList并分配新的Allocator
		void Reset();

		// 设置资源状态
		void SetResourceState(GPUResourceOwnerDX12* resource, D3D12_RESOURCE_STATES after, int32 subresourceIndex = -1);

		// 执行指令
		uint64 Execute(bool waitForCompletion = false);

		// 获取CommandList
		ID3D12GraphicsCommandList* GetCommandList() const
		{
			return m_CommandList;
		}

	public:  // override

		void FrameBegin() override;
		void FrameEnd() override;
		void SetViewport(const Math::Viewport& viewport) override;
		void SetScissor(const Math::Rectangle& scissorRect) override;
		void Clear(GPUTextureView* rt, const Color& color) override;
		void ClearDepth(GPUTextureView* depthBuffer, float depthValue) override;
		void SetRenderTarget(GPUTextureView* rt) override;
		void SetRenderTarget(GPUTextureView* rt, GPUTextureView* depthBuffer) override;
		void BindSR(int32 slot, GPUTextureView* view) override;
		void BindVB(GPUBuffer* vertexBuffer) override;
		void BindIB(GPUBuffer* indexBuffer) override;
		void BindCB(int32 slot, GPUConstantBuffer* cb) override;
		void UpdateCB(GPUConstantBuffer* cb, const void* data) override;
		void UpdateBuffer(GPUBuffer* buffer, const void* data, uint32 size, uint32 offset) override;
		void UpdateTexture(GPUTexture* texture, int32 arrayIndex, int32 mipIndex, const void* data, uint32 rowPitch, uint32 slicePitch) override;
		void DrawIndexedInstanced(uint32 indicesCount, uint32 instanceCount, int32 startIndex = 0, int32 startVertex = 0, int32 startInstance = 0) override;
		void SetState(GPUPipelineState* state) override;
		GPUPipelineState* GetState() const override;
		void ClearState() override;
		void FlushState() override;
		void Flush() override;

	private:

		// 添加资源屏障
		void addResourceBarrier(ID3D12Resource* resource, const D3D12_RESOURCE_STATES before, const D3D12_RESOURCE_STATES after, const int32 subresourceIndex);

		// 当要调用绘制指令时
		void onDrawCall();

		// 设置着色器资源视图
		void flushSRVs();

		// 设置渲染目标视图
		void flushRTVs();
		
		// 设置无序访问视图
		void flushUAVs();

		// 设置常量缓冲区, ConstantBuffer
		void flushCBs();

		// 设置资源屏障, ResourceBarrier
		void flushRBs();

		// 设置PipelineState
		void flushPS();

	private:

		GPUDeviceDX12* m_Device;
		ID3D12GraphicsCommandList* m_CommandList;
		ID3D12CommandAllocator* m_CurrentAllocator;
		GPUPipelineStateDX12* m_CurrentState;

		D3D12_RESOURCE_BARRIER m_ResourceBarrierBuffers[DX12_RB_BUFFER_SIZE];
		int32 m_ResourceBarrierNum;

		GPUConstantBufferDX12* m_ConstantBufferHandles[DX12_MAX_CB_BINDED];

		IShaderResourceDX12* m_ShaderResourceHandles[DX12_MAX_SR_BINDED];

		GPUBufferDX12* m_VertexBufferHandle;
		GPUBufferDX12* m_IndexBufferHandle;

		GPUTextureViewDX12* m_RenderTargetHandle;
		GPUTextureViewDX12* m_DepthTextureHandle;

		bool m_RTDirtyFlag = false;
		bool m_PSDirtyFlag = false;
		bool m_CBDirtyFlag = false;

		uint32 m_SRDirtyMask = 0;
	};

}

#endif