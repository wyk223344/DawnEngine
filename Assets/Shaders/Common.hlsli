
#ifndef _COMMON_HLSLI
#define _COMMON_HLSLI

struct LightData
{
	float4x4 ViewProjMatrix;
	float3 Direction;
	float3 Color;
};

cbuffer GlobalConstants : register(b0)
{
	float4x4 ViewProjMatrix;
	float3 CameraPosition;
	int DirectionalLightCount;
	LightData LightDatas[4];
};


cbuffer MeshConstants : register(b1)
{
	float4x4 WorldMatrix;
};


SamplerState SamplerLinearClamp  : register(s0);
SamplerState SamplerPointClamp   : register(s1);
SamplerState SamplerLinearWrap   : register(s2);
SamplerState SamplerPointWrap    : register(s3);
SamplerComparisonState SamplerShadow       : register(s4);
SamplerComparisonState SamplerShadowPCF    : register(s5);


Texture2D ShadowMap : register(t10);


float CalcShadowFactor(float4 shadowPosH)
{
    // Complete projection by doing division by w.
    shadowPosH.xyz /= shadowPosH.w;

    // Depth in NDC space.
    float depth = shadowPosH.z;

    uint width, height, numMips;
    ShadowMap.GetDimensions(0, width, height, numMips);

    // Texel size.
    float dx = 1.0f / (float)width;

    float percentLit = 0.0f;
    const float2 offsets[9] =
    {
        float2(-dx,  -dx), float2(0.0f,  -dx), float2(dx,  -dx),
        float2(-dx, 0.0f), float2(0.0f, 0.0f), float2(dx, 0.0f),
        float2(-dx,  +dx), float2(0.0f,  +dx), float2(dx,  +dx)
    };

    [unroll]
    for (int i = 0; i < 9; ++i)
    {
        percentLit += ShadowMap.SampleCmpLevelZero(SamplerShadowPCF,
            shadowPosH.xy + offsets[i], depth).r;
    }

    return percentLit / 9.0f;
}


//---------------------------------------------------------------------------------------
// Transforms a normal map sample to world space.
//---------------------------------------------------------------------------------------
float3 NormalSampleToWorldSpace(float3 normalMapSample, float3 unitNormalW, float3 tangentW)
{
    // Uncompress each component from [0,1] to [-1,1].
    float3 normalT = 2.0f * normalMapSample - 1.0f;

    // Build orthonormal basis.
    float3 N = unitNormalW;
    float3 T = normalize(tangentW - dot(tangentW, N) * N);
    float3 B = cross(N, T);

    float3x3 TBN = float3x3(T, B, N);

    // Transform from tangent space to world space.
    float3 bumpedNormalW = mul(normalT, TBN);

    return bumpedNormalW;
}


#endif