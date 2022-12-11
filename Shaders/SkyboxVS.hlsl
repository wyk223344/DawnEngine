#include "Common.hlsli"

struct VertexInput
{
	float3 positionOS  : POSITION;
	float2 uv		   : TEXCOORD;
	float3 normalOS	   : NORMAL;
	float3 tangentOS   : TANGENT;
};

struct VertexOutput
{
	float4 positionCS  : SV_POSITION;
	float3 uv		   : TEXCOORD0;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	float3 positionWS = 5000.0f * input.positionOS + CameraPosition;
	output.positionCS = mul(ViewProjMatrix, float4(positionWS, 1.0f)).xyww;
	output.uv = input.positionOS.xyz;
	return output;
}