
#include "GeometryGenerator.h"
#include "MeshData.h"

using namespace DawnEngine;
using namespace DawnEngine::Math;

MeshData* GeometryGenerator::CreateBox(float width, float height, float depth, uint32 numSubdivisions)
{
	MeshData* meshData = New<MeshData>();

	//
	// Create the vertices.
	//

	Vertex v[24];

	float w2 = 0.5f * width;
	float h2 = 0.5f * height;
	float d2 = 0.5f * depth;

	// Fill in the front face vertex data.
	v[0] = Vertex(-w2, -h2, -d2, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f);
	v[1] = Vertex(-w2, +h2, -d2, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f);
	v[2] = Vertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f);
	v[3] = Vertex(+w2, -h2, -d2, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f);

	// Fill in the back face vertex data.
	v[4] = Vertex(-w2, -h2, +d2, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f);
	v[5] = Vertex(+w2, -h2, +d2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f);
	v[6] = Vertex(+w2, +h2, +d2, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f);
	v[7] = Vertex(-w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8] = Vertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[9] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[10] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[11] = Vertex(+w2, +h2, -d2, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);

	// Fill in the bottom face vertex data.
	v[12] = Vertex(-w2, -h2, -d2, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[13] = Vertex(+w2, -h2, -d2, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[14] = Vertex(+w2, -h2, +d2, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[15] = Vertex(-w2, -h2, +d2, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = Vertex(-w2, -h2, +d2, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);
	v[17] = Vertex(-w2, +h2, +d2, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);
	v[18] = Vertex(-w2, +h2, -d2, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);
	v[19] = Vertex(-w2, -h2, -d2, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);

	// Fill in the right face vertex data.
	v[20] = Vertex(+w2, -h2, -d2, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[21] = Vertex(+w2, +h2, -d2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[22] = Vertex(+w2, +h2, +d2, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[23] = Vertex(+w2, -h2, +d2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	meshData->Vertices.assign(&v[0], &v[24]);

	//
	// Create the indices.
	//

	uint32 i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	meshData->Indices.assign(&i[0], &i[36]);

	return meshData;
}

MeshData* GeometryGenerator::CreateSphere(float radius, uint32 sliceCount, uint32 stackCount)
{
	MeshData* meshData = New<MeshData>();

	//
	// Compute the vertices stating at the top pole and moving down the stacks.
	//

	// Poles: note that there will be texture coordinate distortion as there is
	// not a unique point on the texture map to assign to the pole when mapping
	// a rectangular texture onto a sphere.
	Vertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	Vertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	meshData->Vertices.push_back(topVertex);

	float phiStep = PI / stackCount;
	float thetaStep = 2.0f * PI / sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (uint32 i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i * phiStep;

		// Vertices of ring.
		for (uint32 j = 0; j <= sliceCount; ++j)
		{
			float theta = j * thetaStep;

			Vertex v;

			// spherical to cartesian
			v.Position.X = radius * sinf(phi) * cosf(theta);
			v.Position.Y = radius * cosf(phi);
			v.Position.Z = radius * sinf(phi) * sinf(theta);

			// Partial derivative of P with respect to theta
			v.Tangent.X = -radius * sinf(phi) * sinf(theta);
			v.Tangent.Y = 0.0f;
			v.Tangent.Z = +radius * sinf(phi) * cosf(theta);

			v.Tangent.Normalize();
			v.Normal = v.Position;
			v.Normal.Normalize();

			v.UV.X = theta / TWO_PI;
			v.UV.Y = phi / PI;

			meshData->Vertices.push_back(v);
		}
	}

	meshData->Vertices.push_back(bottomVertex);

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for (uint32 i = 1; i <= sliceCount; ++i)
	{
		meshData->Indices.push_back(0);
		meshData->Indices.push_back(i + 1);
		meshData->Indices.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	uint32 baseIndex = 1;
	uint32 ringVertexCount = sliceCount + 1;
	for (uint32 i = 0; i < stackCount - 2; ++i)
	{
		for (uint32 j = 0; j < sliceCount; ++j)
		{
			meshData->Indices.push_back(baseIndex + i * ringVertexCount + j);
			meshData->Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			meshData->Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			meshData->Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			meshData->Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			meshData->Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	uint32 southPoleIndex = (uint32)meshData->Vertices.size() - 1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;

	for (uint32 i = 0; i < sliceCount; ++i)
	{
		meshData->Indices.push_back(southPoleIndex);
		meshData->Indices.push_back(baseIndex + i);
		meshData->Indices.push_back(baseIndex + i + 1);
	}

	return meshData;
}


MeshData* GeometryGenerator::CreatePlane(float width, float depth, uint32 m, uint32 n)
{
	MeshData* meshData = New<MeshData>();

	uint32 vertexCount = m * n;
	uint32 faceCount = (m - 1) * (n - 1) * 2;

	//
	// Create the vertices.
	//

	float halfWidth = 0.5f * width;
	float halfDepth = 0.5f * depth;

	float dx = width / (n - 1);
	float dz = depth / (m - 1);

	float du = 1.0f / (n - 1);
	float dv = 1.0f / (m - 1);

	meshData->Vertices.resize(vertexCount);
	for (uint32 i = 0; i < m; ++i)
	{
		float z = halfDepth - i * dz;
		for (uint32 j = 0; j < n; ++j)
		{
			float x = -halfWidth + j * dx;

			meshData->Vertices[i * n + j].Position = Vector3(x, 0.0f, z);
			meshData->Vertices[i * n + j].Normal = Vector3(0.0f, 1.0f, 0.0f);
			meshData->Vertices[i * n + j].Tangent = Vector3(1.0f, 0.0f, 0.0f);

			// Stretch texture over grid.
			meshData->Vertices[i * n + j].UV.X = j * du;
			meshData->Vertices[i * n + j].UV.Y = i * dv;
		}
	}

	//
	// Create the indices.
	//

	meshData->Indices.resize(faceCount * 3); // 3 indices per face

	// Iterate over each quad and compute indices.
	uint32 k = 0;
	for (uint32 i = 0; i < m - 1; ++i)
	{
		for (uint32 j = 0; j < n - 1; ++j)
		{
			meshData->Indices[k] = i * n + j;
			meshData->Indices[k + 1] = i * n + j + 1;
			meshData->Indices[k + 2] = (i + 1) * n + j;

			meshData->Indices[k + 3] = (i + 1) * n + j;
			meshData->Indices[k + 4] = i * n + j + 1;
			meshData->Indices[k + 5] = (i + 1) * n + j + 1;

			k += 6; // next quad
		}
	}

	return meshData;
}


MeshData* GeometryGenerator::CreateQuad(float x, float y, float w, float h, float depth)
{
	float halfWidth = w / 2;
	float halfHeight = h / 2;

	MeshData* meshData = New<MeshData>();

	meshData->Vertices.resize(4);
	meshData->Indices.resize(6);

	meshData->Vertices[0] = Vertex(
		x - halfWidth, y - halfHeight, depth,
		0.0f, 1.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f
	);
	meshData->Vertices[1] = Vertex(
		x - halfWidth, y + halfHeight, depth,
		0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f
	);
	meshData->Vertices[2] = Vertex(
		x + halfWidth, y + halfHeight, depth,
		1.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f
	);
	meshData->Vertices[3] = Vertex(
		x + halfWidth, y - halfHeight, depth,
		1.0f, 1.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f
	);

	meshData->Indices[0] = 0;
	meshData->Indices[1] = 1;
	meshData->Indices[2] = 2;

	meshData->Indices[3] = 0;
	meshData->Indices[4] = 2;
	meshData->Indices[5] = 3;

	return meshData;
}


void GeometryGenerator::Subdivide(MeshData& meshData)
{
	// Save a copy of the input geometry.
	MeshData inputCopy = meshData;


	meshData.Vertices.resize(0);
	meshData.Indices.resize(0);

	//       v1
	//       *
	//      / \
	//     /   \
	//  m0*-----*m1
	//   / \   / \
	//  /   \ /   \
	// *-----*-----*
	// v0    m2     v2

	uint32_t numTris = (uint32_t)inputCopy.Indices.size() / 3;
	for (uint32_t i = 0; i < numTris; ++i)
	{
		Vertex v0 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 0]];
		Vertex v1 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 1]];
		Vertex v2 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 2]];

		//
		// Generate the midpoints.
		//

		Vertex m0 = MidPoint(v0, v1);
		Vertex m1 = MidPoint(v1, v2);
		Vertex m2 = MidPoint(v0, v2);

		//
		// Add new geometry.
		//

		meshData.Vertices.push_back(v0); // 0
		meshData.Vertices.push_back(v1); // 1
		meshData.Vertices.push_back(v2); // 2
		meshData.Vertices.push_back(m0); // 3
		meshData.Vertices.push_back(m1); // 4
		meshData.Vertices.push_back(m2); // 5

		meshData.Indices.push_back(i * 6 + 0);
		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 5);

		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 4);
		meshData.Indices.push_back(i * 6 + 5);

		meshData.Indices.push_back(i * 6 + 5);
		meshData.Indices.push_back(i * 6 + 4);
		meshData.Indices.push_back(i * 6 + 2);

		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 1);
		meshData.Indices.push_back(i * 6 + 4);
	}
}


Vertex GeometryGenerator::MidPoint(const Vertex& v0, const Vertex& v1)
{
	Vertex v;
	v.Position = (v0.Position + v1.Position) / 2;
	v.Normal = (v0.Normal + v1.Normal) / 2;
	v.Normal.Normalize();
	v.Tangent = (v0.Tangent + v1.Tangent) / 2;
	v.Tangent.Normalize();
	v.UV = (v0.UV + v1.UV) / 2;
	return v;
}
