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
	float3 positionWS = 5000.0f * input.positionOS;
	output.positionCS = mul(ViewProjMatrix, float4(positionWS, 1.0f)).xyww;
	// output.positionCS.z -= 0.01f;	// TODO: 不加这个天空盒会被截掉，但是龙书样例里没有这个也正常，奇怪
	output.uv = input.uv;
	output.color = input.positionOS.xyz;
	return output;
}