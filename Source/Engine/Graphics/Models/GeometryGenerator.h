#pragma once

#include "Engine/Core/Include.h"
#include "Vertex.h"

namespace DawnEngine
{

	class MeshData;

	class GeometryGenerator
	{
	public:

		static MeshData CreateBox(float width, float height, float depth, uint32 numSubdivisions = 0);

		static void Subdivide(MeshData& meshData);

		static Vertex MidPoint(const Vertex& v0, const Vertex& v1);
	};
}