#include "Common.hlsli"

TextureCube SkyboxTexture  : register(t0);

//float PITemp = 3.14159265359;

struct VertexOutput
{
	float4 positionCS  : SV_POSITION;
	float3 uv		   : TEXCOORD0;
};

float4 main(VertexOutput input) : SV_TARGET
{
	float4 diffuseAlbedo = SkyboxTexture.Sample(SamplerLinearClamp, input.uv);

	return float4(diffuseAlbedo.xyz, 1.0f);
	float temp = 3.1415;

	float3 irradiance = float3(0.0f, 0.0f, 0.0f);
	float3 normal = normalize(input.uv);
	float3 up = float3(0.0f, 1.0f, 0.0f);
	float3 right = normalize(cross(up, normal));
	up = normalize(cross(normal, right));

	float sampleDelta = 0.04f;
	float numSamples = 0.0f;

	// 在半球上采样
	for (float phi = 0.0f; phi < 2.0f * temp; phi += sampleDelta)
	{
		for (float theta = 0.0f; theta < 0.5f * temp; theta += sampleDelta)
		{
			// spherical to cartesian (in tangent space)
			float3 tangentSample = float3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
			// tangent space to world
			float3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * normal;

			irradiance += SkyboxTexture.Sample(SamplerLinearClamp, sampleVec).rgb * cos(theta) * sin(theta);
			numSamples++;
		}
	}

	irradiance = temp * irradiance * (1.0f / numSamples);

	return float4(irradiance, 1.0f);
}