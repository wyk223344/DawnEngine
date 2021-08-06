





float3 FresnelSchlick(float NdotV, float3 F0)
{
	return F0 + (1.0 - F0) * pow(max(1.0f - NdotV, 0.0f), 5.0f);
}