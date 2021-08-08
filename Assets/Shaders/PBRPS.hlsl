#include "Common.hlsli"
#include "Lighting.hlsli"

struct VertexOutput
{
	float4 positionCS  : SV_POSITION;
	float2 uv		   : TEXCOORD0;
	float3 positionWS  : TEXCOORD1;
	float3 normalWS	   : TEXCOORD2;
	float3 tangentWS   : TEXCOORD3;
};

Texture2D AlbedoMap : register(t0);
Texture2D NormalMap : register(t1);
Texture2D MetallicMap : register(t2);
Texture2D RoughnessMap : register(t3);
Texture2D AOMap : register(t4);





float4 main(VertexOutput input) : SV_TARGET
{
	float3 albedo = AlbedoMap.Sample(SamplerLinearClamp, input.uv).rgb;
	float metallic = MetallicMap.Sample(SamplerLinearClamp, input.uv).r;
	float roughness = RoughnessMap.Sample(SamplerLinearClamp, input.uv).r;
	float ao = AOMap.Sample(SamplerLinearClamp, input.uv).r;
	// TODO: 法线贴图的采样器有些问题，之后待调整
	float4 normalMapSample = NormalMap.Sample(SamplerLinearClamp, input.uv);

	float3 positionWS = input.positionWS;
	float3 normalWS = normalize(input.normalWS);
	float3 tangentWS = normalize(input.tangentWS);
	float3 V = normalize(CameraPosition - positionWS);
	float3 N = NormalSampleToWorldSpace(normalMapSample.rgb, normalWS, tangentWS);

	float3 F0 = float3(0.04f, 0.04f, 0.04f);
	F0 = lerp(F0, albedo, metallic);

	float3 Lo = float3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < DirectionalLightCount; i++)
	{
		LightData mainLight = LightDatas[i];
		float3 lightColor = mainLight.Color;
		float3 L = -normalize(mainLight.Direction);
		float3 H = normalize(L + V);
		float3 radiance = lightColor;

		// Cook-Torrance BRDF
		float D = DistributionGGX(N, H, roughness);
		float G = GeometrySmith(N, V, L, roughness);
		float3 F = FresnelSchlick(max(dot(H, V), 0.0f), F0);

		float3 numerator = D * G * F;
		float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
		float3 specular = numerator / denominator;

		float3 kS = F;
		float3 kD = float3(1.0f, 1.0f, 1.0f) - kS;
		kD *= 1.0f - metallic;
		float NdotL = max(dot(N, L), 0.0);
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;
	}

	float3 ambient = albedo * ao * 0.03f + Lo;

	float3 color = ambient;

	// HDR tonemapping
	color = color / (color + float3(1.0f, 1.0f, 1.0f));
	// gamma correct
	color = pow(color, 1.0f / 2.2f);

	return float4(color, 1.0f);
}