

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
};



VertexOutput main(VertexInput input)
{
	VertexOutput output;
	output.positionCS = float4(input.positionOS, 1.0f);
	output.uv = input.uv;
	return output;
}