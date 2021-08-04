
struct LightData
{
	float4x4 ViewProjMatrix;
	float3 Direction;
};

cbuffer GlobalConstants : register(b0)
{
	float4x4 ViewProjMatrix;
	float3 CameraPosition;
	int DirectionalLightCount;
	LightData LightDatas[4];
};


cbuffer MeshConstants : register(b1)
{
	float4x4 WorldMatrix;
};


SamplerState SamplerLinearClamp  : register(s0);
SamplerState SamplerPointClamp   : register(s1);
SamplerState SamplerLinearWrap   : register(s2);
SamplerState SamplerPointWrap    : register(s3);
SamplerState SamplerShadow       : register(s4);
SamplerState SamplerShadowPCF    : register(s5);
