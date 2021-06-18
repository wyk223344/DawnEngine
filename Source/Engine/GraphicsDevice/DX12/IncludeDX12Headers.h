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
#include "d3dx12.h"
#include "d3dUtil.h"
#include "UploadBuffer.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#define D3D12_GPU_VIRTUAL_ADDRESS_NULL      ((D3D12_GPU_VIRTUAL_ADDRESS)0)
#define D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN   ((D3D12_GPU_VIRTUAL_ADDRESS)-1)


#endif