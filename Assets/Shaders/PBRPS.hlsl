#include "Common.hlsli"

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

	float3 positionWS = input.positionWS;
	float3 normalWS = input.normalWS;
	float3 tangentWS = input.tangentWS;
	float3 viewPositionWS = normalize(CameraPosition - positionWS);


	float3 ambient = albedo * ao * 0.03f;



	float3 color = ambient;
	// HDR tonemapping
	//color = color / (color + float3(1.0f, 1.0f, 1.0f));
	// gamma correct
	//color = pow(color, 1.0f / 2.2f);

	return float4(color, 1.0f);
}