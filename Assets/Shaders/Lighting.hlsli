#ifndef _LIGHTING_HLSLI
#define _LIGHTING_HLSLI

const float PI = 3.14159265359;


/*
   D项：法线分布函数  Normal Distribution Function
   估算在受到表面粗糙度的影响下，取向方向与中间向量一致的微平面的数量。这是用来估算微平面的主要函数。
*/
// Trowbridge-Reitz GGX法线分布函数
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
   G项：几何函数
   描述了微平面自成阴影的属性。当一个平面相对比较粗糙的时候，平面表面上的微平面有可能挡住其他的微平面从而减少表面所反射的光线。
*/
// Schlick-GGX
float GeometrySchlickGGX(float NdotV, float k)
{
    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

// Smith’s method
float GeometrySmith(float3 N, float3 V, float3 L, float k)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    // 观察方向 （几何遮蔽）
    float ggx1 = GeometrySchlickGGX(NdotV, k);
    // 光线方向  (几何阴影)
    float ggx2 = GeometrySchlickGGX(NdotL, k);

    return ggx1 * ggx2;
}


/*
   F项：菲涅尔方程
   菲涅尔方程描述的是在不同的表面角下表面所反射的光线所占的比率。
*/
// Fresnel Schlick近似
float3 FresnelSchlick(float NdotV, float3 F0)
{
	return F0 + (1.0 - F0) * pow(max(1.0f - NdotV, 0.0f), 5.0f);
}

#endif