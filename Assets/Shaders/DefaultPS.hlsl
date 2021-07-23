
#include "Common.hlsli"

struct VertexOutput
{
	float4 positionCS  : SV_POSITION;
	float2 uv		   : TEXCOORD0;
	float3 positionWS  : TEXCOORD1;
};

float4 main(VertexOutput input) : SV_TARGET
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}