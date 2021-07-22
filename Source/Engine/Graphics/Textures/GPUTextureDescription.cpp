#include "GPUTextureDescription.h"

using namespace DawnEngine;


void GPUTextureDescription::Clear()
{
	Platform::MemoryClear(this, sizeof(GPUTextureDescription));
	MultiSampleLevel = MSAALevel::None;
}

GPUTextureDescription GPUTextureDescription::New2D(int32 width, int32 height, PixelFormat format, GPUTextureFlags textureFlags, int32 mipCount, int32 arraySize, MSAALevel msaaLevel)
{
    GPUTextureDescription desc;
    desc.Dimensions = TextureDimensions::Texture;
    desc.Width = width;
    desc.Height = height;
    desc.Depth = 1;
    desc.ArraySize = arraySize;
    desc.MipLevels = 1;
    desc.Format = format;
    desc.MultiSampleLevel = msaaLevel;
    desc.Flags = textureFlags;
    desc.DefaultClearColor = Color::Black;
    return desc;
}

GPUTextureDescription GPUTextureDescription::NewCube(int32 size, PixelFormat format, GPUTextureFlags textureFlags, int32 mipCount)
{
    auto desc = New2D(size, size, format, textureFlags, mipCount, 6, MSAALevel::None);
    desc.Dimensions = TextureDimensions::CubeTexture;
    return desc;
}