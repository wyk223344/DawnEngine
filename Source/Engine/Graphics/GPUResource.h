#pragma once

#include "Engine/Core/Include.h"

namespace DawnEngine
{
	/*
		资源
	*/
	class GPUResource : Object
	{
	public:

		void ReleaseGPU()
		{
			if (m_MemoryUsage != 0)
			{
				OnReleaseGPU();
				m_MemoryUsage = 0;
			}
		}

	protected:

		virtual void OnReleaseGPU()
		{
		}

	protected:

		uint64 m_MemoryUsage = 0;
	};

	/*
		资源视图，资源描述符的持有者
	*/
	class GPUResourceView : Object
	{
	public:
	};

	/*
		持有device引用的资源。主要为图形api层使用
	*/
	template<class DeviceType, class BaseType>
	class GPUResourceBase : public BaseType
	{
	public:

		GPUResourceBase(DeviceType* device) noexcept
			: m_Device(device)
		{
		}

		void InitDevice(DeviceType* device)
		{
			m_Device = device;
		}

	protected:

		DeviceType* m_Device;
	};

	/*
		图形api资源的实际持有者，如：ID3D12Resource。 主要为图形api层使用
	*/
	class GPUResourceOwner
	{

	};
}