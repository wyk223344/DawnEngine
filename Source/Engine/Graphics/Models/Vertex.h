#pragma once

#include "Engine/Core/Include.h"

namespace DawnEngine
{
	struct Vertex
	{
	public:

		Vertex()
			: Position(0.0f, 0.0f, 0.0f)
			, UV(0.0f, 0.0f)
			, Normal(0.0f, 1.0f, 0.0f)
			, Tangent(1.0f, 0.0f, 0.0f)
		{
		}

		~Vertex()
		{
		}

		Vertex(float positionX, float positionY, float positionZ,
			float u, float v,
			float normalX = 0.0f, float normalY = 1.0f, float normalZ = 0.0f,
			float tangentX = 1.0f, float tangentY = 0.0f, float tangentZ = 0.0f)
			: Position(positionX, positionY, positionZ)
			, UV(u, v)
			, Normal(normalX, normalY, normalZ)
			, Tangent(tangentX, tangentY, tangentZ)
		{
		}

		Math::Vector3 Position;
		Math::Vector2 UV;
		Math::Vector3 Normal;
		Math::Vector3 Tangent;
	};
}