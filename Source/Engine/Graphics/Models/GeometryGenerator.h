#pragma once

#include "Engine/Core/Include.h"
#include "Vertex.h"

namespace DawnEngine
{

	class MeshData;

	class GeometryGenerator
	{
	public:

		static MeshData* CreateBox(float width, float height, float depth, uint32 numSubdivisions = 0);

		static MeshData* CreateSphere(float radius, uint32 sliceCount, uint32 stackCount);

		static MeshData* CreatePlane(float width, float depth, uint32 m, uint32 n);

		static void Subdivide(MeshData& meshData);

		static Vertex MidPoint(const Vertex& v0, const Vertex& v1);
	};
}