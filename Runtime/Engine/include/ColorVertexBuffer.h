#pragma once
#include "RenderResource.h"
struct StaticMeshBuildVertex;

class ColorVertexBuffer :public VertexBuffer
{
public:
private:
	class ColorVertexData* vertexData;
	uint8* data;
	uint32 stride;
	uint32 numVertices;
	bool needCPUAccess = true;
};

