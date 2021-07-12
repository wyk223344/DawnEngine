//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer GlobalConstants : register(b0)
{
	float4x4 ViewProjMatrix;
};

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
	float3 color	   : TEXCOORD;
};

VertexOut VS(VertexIn input)
{
	VertexOut output;

	output.positionCS = mul(ViewProjMatrix, float4(input.positionOS, 1.0f));

	output.color = input.positionOS.xyz + 0.5f;
    return output;
}

float4 PS(VertexOut input) : SV_Target
{
	return float4(input.color, 1.0f);
	// return float4(1.0f, 0.0f, 0.0f, 1.0f);
    //return float4(input.uv.x, input.uv.y, 0.0f, 1.0f);
}


