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
	float depth = CopyMap.Sample(SamplerLinear, input.uv).r;
	depth = (1.0f - depth) * 0.6f;
	return float4(depth, 0.0f, 0.0f, 1.0f);
}