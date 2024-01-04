#pragma once
#include "Platform.h"

struct MeshReductionSettings
{
	float precentTriangles;
	float maxNumOfTriangles;
	float precentVertices;
	uint32 maxNumOfVerts;
	float maxDeviation;
	float pixelError;
	float wildingThreashold;
	float hardAngleThreashold;
	uint32 baseLODModel;
	uint8 bRecalculateNormals:1;
	uint8 generateUniqueLightMapUVS:1;
	uint8 keepSymmetry:1;
	uint8 visibilityAided:1;
	uint8 cullOccluded:1;
};
