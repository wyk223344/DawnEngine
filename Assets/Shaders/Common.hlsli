
struct LightData
{
	float3 Direction;
};

cbuffer GlobalConstants : register(b1)
{
	float4x4 ViewProjMatrix;
	float3 CameraPosition;
	LightData LightDatas[4];
};


cbuffer MeshConstants : register(b0)
{
	float4x4 WorldMatrix;
};