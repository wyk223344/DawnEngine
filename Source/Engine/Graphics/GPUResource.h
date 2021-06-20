#pragma once

#include "Engine/Core/Enums.h"

namespace DawnEngine
{
	/*
	*/
	class GPUResource
	{
	public:
	};

	/*
	*/
	template<class DeviceType, class BaseType>
	class GPUResourceBase : public BaseType
	{
	public:

		GPUResourceBase(DeviceType* device)
			: m_Device(device)
		{
		}

	protected:
		DeviceType* m_Device;
	};
}