//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject : register(b0)
{
	float4x4 gWorldViewProj; 
	float gTime;
};

struct VertexIn
{
	float3 positionOS  : POSITION;
    float2 uv		   : TEXCOORD;
};

struct VertexOut
{
	float4 positionCS  : SV_POSITION;
	float2 uv		   : TEXCOORD;
};

VertexOut VS(VertexIn input)
{
	VertexOut output;
	
	output.positionCS = float4(input.positionOS.x, input.positionOS.y, input.positionOS.z, 1.0f);
    
    return output;
}

float4 PS(VertexOut pin) : SV_Target
{
    return float4(1.0f, 1.0f, 0.0f, 1.0f);
}


