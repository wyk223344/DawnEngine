#ifndef _LIGHTING_HLSLI
#define _LIGHTING_HLSLI

const float PI = 3.14159265359;


/*
   D����߷ֲ�����  Normal Distribution Function
   �������ܵ�����ֲڶȵ�Ӱ���£�ȡ�������м�����һ�µ�΢ƽ���������������������΢ƽ�����Ҫ������
*/
// Trowbridge-Reitz GGX���߷ֲ�����
float DistributionGGX(float3 N, float3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

/*
   G����κ���
   ������΢ƽ���Գ���Ӱ�����ԡ���һ��ƽ����ԱȽϴֲڵ�ʱ��ƽ������ϵ�΢ƽ���п��ܵ�ס������΢ƽ��Ӷ����ٱ���������Ĺ��ߡ�
*/
// Schlick-GGX
float GeometrySchlickGGX(float NdotV, float k)
{
    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

// Smith��s method
float GeometrySmith(float3 N, float3 V, float3 L, float k)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    // �۲췽�� �������ڱΣ�
    float ggx1 = GeometrySchlickGGX(NdotV, k);
    // ���߷���  (������Ӱ)
    float ggx2 = GeometrySchlickGGX(NdotL, k);

    return ggx1 * ggx2;
}


/*
   F�����������
   �������������������ڲ�ͬ�ı�����±���������Ĺ�����ռ�ı��ʡ�
*/
// Fresnel Schlick����
float3 FresnelSchlick(float NdotV, float3 F0)
{
	return F0 + (1.0 - F0) * pow(max(1.0f - NdotV, 0.0f), 5.0f);
}

#endif