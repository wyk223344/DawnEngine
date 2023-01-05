
#include "Common.hlsli"

cbuffer MaterialConstants : register(b2)
{
	float3 MainColor;
};

struct VertexOutput
{
	float4 positionCS  : SV_POSITION;
	float2 uv		   : TEXCOORD0;
	float3 positionWS  : TEXCOORD1;
	float3 normalWS	   : TEXCOORD2;
	float3 tangentWS   : TEXCOORD3;
};

float4 main(VertexOutput input) : SV_TARGET
{
	// return float4(DirectionalLightCount, 0.0f, 0.0f, 1.0f);

	float3 positionWS = input.positionWS;
	float3 normalWS = normalize(input.normalWS);
	float3 tangentWS = normalize(input.tangentWS);
	float3 viewPositionWS = normalize(CameraPosition - positionWS);

	LightData mainLight = LightDatas[0];
	float3 lightDir = mainLight.Direction;
	float3 lightColor = mainLight.Color;

	float NdotL = max(dot(-lightDir, normalWS), 0.0f);

	// shadow
	float4 shadowPosCS = mul(mainLight.ViewProjMatrix, float4(positionWS, 1.0f));

	// return shadowPosCS;
	float shadowFactor = CalcShadowFactor(shadowPosCS);

	// return float4(shadowFactor, 0.0f, 0.0f, 1.0f);

	float3 finalColor = MainColor * NdotL * shadowFactor;

	return float4(finalColor, 1.0f);
}