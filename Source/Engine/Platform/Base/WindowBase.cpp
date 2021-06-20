
#include "Engine/Platform/Base/WindowBase.h"
#include "Engine/Platform/WindowsManager.h"
#include "Engine/Graphics/GPUDevice.h"

using namespace DawnEngine;

WindowBase::WindowBase(const CreateWindowSettings& settings)
{
	m_Width = settings.Width;
	m_Height = settings.Height;
	m_SwapChain = nullptr;

	WindowsManager::Register((Window*)this);

	InitSwapChain();
}

WindowBase::~WindowBase()
{
}

bool WindowBase::InitSwapChain()
{
	if (m_SwapChain == nullptr)
	{
		m_SwapChain = GPUDevice::Instance->CreateSwapChain((Window*)this);
		if (!m_SwapChain)
		{
			return false;
		}
	}

	return true;
}
