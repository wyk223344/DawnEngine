#if GRAPHICS_API_DIRECTX12

#include "GPUShaderProgramDX12.h"
#include "Engine/Graphics/Shaders/GPUShaderProgram.h"

#include "IncludeDX12Headers.h"

#include <comdef.h>
#include <d3dcompiler.h>


using namespace DawnEngine::DX12;

#pragma region GPUShaderProgramVSDX12


std::wstring StringToWString(const std::string str)
{

	std::wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}


bool GPUShaderProgramVSDX12::Init(std::string filePath)
{
	UINT compileFlags = 0;
	HRESULT hr = S_OK;
	ID3DBlob* errors;
	hr = D3DCompileFromFile(StringToWString(filePath).c_str(), nullptr, ((ID3DInclude*)(UINT_PTR)1),
		"VS", "vs_5_0", compileFlags, 0, &m_ByteCode, &errors);

	ThrowIfFailed(hr);
	return true;
}

#pragma endregion

#pragma region GPUShaderProgramPSDX12

bool GPUShaderProgramPSDX12::Init(std::string filePath)
{
	UINT compileFlags = 0;
	HRESULT hr = S_OK;
	ID3DBlob* errors;
	hr = D3DCompileFromFile(StringToWString(filePath).c_str(), nullptr, ((ID3DInclude*)(UINT_PTR)1),
		"PS", "ps_5_0", compileFlags, 0, &m_ByteCode, &errors);

	ThrowIfFailed(hr);
	return true;
}

#pragma endregion


#endif