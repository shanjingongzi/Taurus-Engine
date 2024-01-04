#pragma once

#include "RenderResource.h"
#include <Vector.hpp>
struct PositionVertex
{
	Vector3f position;
};

class PositionVertexBuffer :public VertexBuffer
{
public:
	uint8* data;
	uint32 stride;
	uint32 numVertices;
	bool needsCPUAccess = true;
};
