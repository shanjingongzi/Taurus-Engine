#pragma once
#include "BoxSphereBounds.hpp"
#include <string>
#include <vector>
#include "StaticMeshLODResources.h"
#include "StaticMeshResource.h"
#define MAX_STATIC_MESH_LODS 8
class StaticMeshRenderData
{
public:
	bool isInitialized;
	StaticMeshRenderData* nextCachedRenderData;
	bool LODsShaderStaticLighting;
	bool readyForStreaming;
	int numInlineLODS;
	int currentFirstLODIdx;
	int LODBiasModifier;
	std::string derivedDataKey;
	std::vector<int>materialIndexToImportIndex;
	std::vector<class MeshUVChannelInfo>UVCchannelDataMaterial;
	long estimatedCompressSize = 0;
	long estimatedNaniteTotalCompressedSize = 0;
public:
	StaticMeshRenderData();
	~StaticMeshRenderData();
	float screenSize[MAX_STATIC_MESH_LODS];
	StaticMeshLODResourcesArray LODResource;
	StaticMeshVertexFactoriesArray LODVertexFactories;
	BoxSphereBounds bounds;
	bool IsInitialized()const
	{
		return isInitialized;
	}
		
private:
};

