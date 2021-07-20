
struct VertexOutput
{
	float4 positionCS  : SV_POSITION;
	float2 uv		   : TEXCOORD0;
	float3 color	   : TEXCOORD1;
};

float4 main(VertexOutput input) : SV_TARGET
{
	return float4(input.color, 1.0f);
}