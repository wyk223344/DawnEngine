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
	float2 uv		   : TEXCOORD0;
	float3 positionWS  : TEXCOORD1;
	float3 normalWS	   : TEXCOORD2;
	float3 tangentWS   : TEXCOORD3;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	float3 positionWS = mul(WorldMatrix, float4(input.positionOS, 1.0f)).xyz;
	output.positionCS = mul(ViewProjMatrix, float4(positionWS, 1.0f));
	output.uv = input.uv;
	output.positionWS = positionWS;
	// output.normalWS = mul(input.normalOS, (float3x3)WorldMatrix);
	output.normalWS = mul((float3x3)WorldMatrix, input.normalOS);
	// output.tangentWS = mul(input.tangentOS, (float3x3)WorldMatrix);
	output.tangentWS = mul((float3x3)WorldMatrix, input.tangentOS);
	return output;
}