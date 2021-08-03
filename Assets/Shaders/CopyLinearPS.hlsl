struct VertexOutput
{
	float4 positionCS  : SV_POSITION;
	float2 uv		   : TEXCOORD0;
};


Texture2D CopyMap : register(t0);
SamplerState SamplerLinear  : register(s0);


float4 main(VertexOutput input) : SV_TARGET
{
	return float4(CopyMap.Sample(SamplerLinear, input.uv).rgb, 1.0f);
}