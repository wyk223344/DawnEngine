struct VertexOutput
{
	float4 positionCS  : SV_POSITION;
	float2 uv		   : TEXCOORD0;
};



float4 main(VertexOutput input) : SV_TARGET
{
	return float4(0.0f, 0.0f, 1.0f, 1.0f);
}