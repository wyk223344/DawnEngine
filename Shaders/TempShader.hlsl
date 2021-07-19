//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer GlobalConstants : register(b0)
{
	float4x4 ViewProjMatrix;
};

Texture2D    DiffuseMap		: register(t0);
SamplerState SamplerLinear  : register(s0);

struct VertexIn
{
	float3 positionOS  : POSITION;
    float2 uv		   : TEXCOORD;
	float3 normalOS	   : NORMAL;
	float3 tangentOS   : TANGENT;
};

struct VertexOut
{
	float4 positionCS  : SV_POSITION;
	float2 uv		   : TEXCOORD0;
	float3 color	   : TEXCOORD1;
};

VertexOut VS(VertexIn input)
{
	VertexOut output;

	output.positionCS = mul(ViewProjMatrix, float4(input.positionOS, 1.0f));
	output.uv = input.uv;
	output.color = input.positionOS.xyz + 0.5f;
    return output;
}

float4 PS(VertexOut input) : SV_Target
{
	float4 diffuseAlbedo = DiffuseMap.Sample(SamplerLinear, input.uv);
	// return float4(input.uv, 1.0f, 1.0f);
	return float4(diffuseAlbedo.xyz, 1.0f);
	// return float4(1.0f, 0.0f, 0.0f, 1.0f);
    //return float4(input.uv.x, input.uv.y, 0.0f, 1.0f);
}


