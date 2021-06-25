
#include "Engine/Graphics/GPUDevice.h"


using namespace DawnEngine;


GPUDevice* GPUDevice::Instance = nullptr;


bool GPUDevice::Init()
{
	return true;
}

void GPUDevice::Draw()
{
	auto context = GetMainContext();

	context->FrameBegin();
	context->FrameEnd();

}

void GPUDevice::Dispose()
{

}
