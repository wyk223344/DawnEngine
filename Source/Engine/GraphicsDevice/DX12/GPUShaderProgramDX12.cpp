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
	//��ȡ��������С��������ռ䣬��������С���ַ�����  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //����ַ�����β  
	//ɾ��������������ֵ  
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