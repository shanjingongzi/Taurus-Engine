#pragma once
#include "Vector2.hpp"
#include "Vector.hpp"
#include "Vector4.hpp"
namespace Lightmass
{
	enum { MAX_TEXCOORDS = 4 };

	class Guid
	{

	};

	struct MeshFileHeader
	{
		unsigned int  Cookie;
	};

	struct FBaseMeshData
	{
		Guid guid;
	};

	struct StaticMeshData
	{
		unsigned int lightmapCoordinateIndex;
		unsigned int numLODs;
	};
	struct StaticMeshLODData
	{
		unsigned int numElements;
		unsigned int numTriangles;
		unsigned int numIndeices;
		unsigned int numVertices;
	};

	struct StaticMeshElementData
	{
		unsigned int firstIndex;
		unsigned int numTriangles;
		unsigned int enableShadowCasting : 1;
	};

	struct StaticMeshVertex
	{

		Vector4f position;
		Vector4f TangentX;
		Vector4f TangentY;
		Vector4f TangentZ;
		Vector2f UVS[MAX_TEXCOORDS];
	};
}