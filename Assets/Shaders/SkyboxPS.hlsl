#include "Common.hlsli"

TextureCube SkyboxTexture  : register(t0);
SamplerState SamplerLinear  : register(s0);

struct VertexOutput
{
	float4 positionCS  : SV_POSITION;
	float3 uv		   : TEXCOORD0;
};

float4 main(VertexOutput input) : SV_TARGET
{
	float4 diffuseAlbedo = SkyboxTexture.Sample(SamplerLinear, input.uv);
	return float4(diffuseAlbedo.xyz, 1.0f);
}