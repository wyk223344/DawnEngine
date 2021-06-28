#pragma once

#include "Engine/Core/Include.h"

namespace DawnEngine
{
	/*
		��Դ
	*/
	class GPUResource : Object
	{
	public:
	};

	///*
	//	��Դ��ͼ
	//*/
	//class GPUResourceView : Object
	//{
	//public:
	//};

	/*
		����device���õ���Դ����ҪΪͼ��api��ʹ��
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
		ͼ��api��Դ��ʵ�ʳ����ߣ��磺ID3D12Resource�� ��ҪΪͼ��api��ʹ��
	*/
	class GPUResourceOwner : Object
	{

	};
}