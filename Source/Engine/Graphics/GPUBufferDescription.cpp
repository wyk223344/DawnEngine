#include "Engine/Core/Include.h"
#include "GPUBufferDescription.h"

using namespace DawnEngine;


void GPUBufferDescription::Clear()
{
	Platform::MemoryClear(this, sizeof(GPUBufferDescription));
}