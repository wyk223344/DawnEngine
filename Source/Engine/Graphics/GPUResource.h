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
	};

	///*
	//	资源视图
	//*/
	//class GPUResourceView : Object
	//{
	//public:
	//};

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

	protected:

		DeviceType* m_Device;
	};

	/*
		图形api资源的实际持有者，如：ID3D12Resource。 主要为图形api层使用
	*/
	class GPUResourceOwner : Object
	{

	};
}