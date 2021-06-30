#pragma once

#if GRAPHICS_API_DIRECTX12

#include <wrl.h>
#include <memory.h>
#include <vector>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cassert>
#include <unordered_map>
#include <d3d12.h>
#include <d3dcommon.h>
#include <dxgi1_4.h>
#include <string>
#include <DirectXCollision.h>
#include <Windows.h>
#include <DirectXMath.h>
#include <cstdint>

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#define D3D12_GPU_VIRTUAL_ADDRESS_NULL      ((D3D12_GPU_VIRTUAL_ADDRESS)0)
#define D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN   ((D3D12_GPU_VIRTUAL_ADDRESS)-1)

#define DX12_BACK_BUFFER_COUNT 2
#define DX12_RB_BUFFER_SIZE 16

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    if(FAILED(hr__))                                                  \
    {                                                                 \
        LOG_ERROR("ThrowIfFailed %s %d", __FILE__, __LINE__);         \
    }                                                                 \
}
#endif


namespace DawnEngine::DX12
{
    class RenderToolsDX12
    {
    public:
        static PixelFormat ToPixelFormat(const DXGI_FORMAT format)
        {
            return static_cast<PixelFormat>(format);
        }

        static DXGI_FORMAT ToDxgiFormat(const PixelFormat format)
        {
            return static_cast<DXGI_FORMAT>(format);
        }
    };
}

#endif