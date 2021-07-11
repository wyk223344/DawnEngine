//***************************************************************************************
// color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer GlobalConstants : register(b0)
{
	float4x4 ViewProjMatrix;
};

struct VertexIn
{
	float3 positionOS  : POSITION;
    float2 uv		   : TEXCOORD;
	float3 normalOS	   : NORMAL;
	float3 tangentOS   : TANGENT;
};

struct VertexOut
{
	float4 positionCS  : SV_POSITION;
	float2 uv		   : TEXCOORD;
};

VertexOut VS(VertexIn input)
{
	VertexOut output;
	
	// output.positionCS = mul(ViewProjMatrix, float4(input.positionOS, 1.0f));
    
	float posX = 0.0f;
	float posY = 0.0f;
	if (input.positionOS.x > 0.0f)
	{
		posX = 1.0f;
	}
	else
	{
		posX = -1.0f;
	}
	if (input.positionOS.y > 0.0f)
	{
		posY = 1.0f;
	}
	else
	{
		posY = -1.0f;
	}
	posX = input.positionOS.y;
	posY = input.positionOS.x;
	output.positionCS = float4(posX, posY, 1.0f, 1.0f);
	output.positionCS = float4(input.positionOS.x, input.positionOS.y, input.positionOS.z + 0.5, 1.0f);

	float4x4 tempMatrix;
	tempMatrix[0] = float4(1.0f, 0.0f, 0.0f, 0.0f);
	tempMatrix[1] = float4(0.0f, 1.0f, 0.0f, 0.0f);
	tempMatrix[2] = float4(0.0f, 0.0f, 1.0f, 0.5f);
	tempMatrix[3] = float4(0.0f, 0.0f, 0.0f, 1.0f);
	output.positionCS = mul(tempMatrix, float4(input.positionOS, 1.0f));
	output.positionCS = mul(ViewProjMatrix, float4(input.positionOS, 1.0f));
	// output.positionCS = mul(float4(input.positionOS, 1.0f), ViewProjMatrix);
	//output.positionCS = mul(float4(input.positionOS, 1.0f), tempMatrix);
	output.uv.x = input.positionOS.x + 0.5f;
	output.uv.y = input.positionOS.y + 0.5f;
    return output;
}

float4 PS(VertexOut input) : SV_Target
{
    return float4(input.uv.x, input.uv.y, 0.0f, 1.0f);
}


