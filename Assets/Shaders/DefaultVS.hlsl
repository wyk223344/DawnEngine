
cbuffer GlobalConstants : register(b0)
{
	float4x4 ViewProjMatrix;
};

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
	float3 color	   : TEXCOORD1;
};

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	output.positionCS = mul(ViewProjMatrix, float4(input.positionOS, 1.0f));
	output.uv = input.uv;
	output.color = input.positionOS.xyz + 0.5f;
	return output;
}