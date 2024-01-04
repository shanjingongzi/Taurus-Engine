#pragma once
#include "Platform.h"
#include "Components.h"
#include <Array.hpp>
#include <BoxSphereBounds.hpp>
#include <map>
#include "MeshMerging.h"
#include "PositionVertexBuffer.h"
#include "ColorVertexBuffer.h"
#include "RawIndexBuffer.h"
#include "RefCounting.h"
#include "MeshUVChannelInfo.h"

#define MAX_STATIC_MESH_LODS 8

struct StaticMaterial;

class StaticMeshLOGGroup
{
private:
	int32 defaultNumLODS;
	int32 defaultMaxNumStreamedLODs;
	int32 defaultMaxNumOptionalLODs;
	int32 defaultLightMapResolution;
	float basePercentTrianglesMult;
	float basePercentVerticesMult;
	bool supportLODStreaming;
	std::string displayName;
	MeshReductionSettings defaultSettings[MAX_STATIC_MESH_LODS];
	MeshReductionSettings settingsBias;

};

class StaticMeshLODSettings
{
private:
	std::map<std::string, StaticMeshLOGGroup>groups;
	std::map<std::string, int32>groupName2Index;
};

struct StaticMeshSection
{
	int32 materialIndex;
	uint32 firstIndex;
	uint32 numTriangles;
	uint32 minVertexIndex;
	uint32 maxVertexIndex;
	bool enableCollision;
	bool castShadow;
	bool visibleInRayTracing;
	bool affectDistanceFieldLighting;
	bool forceOpaque;
	float UVDensities;
	float weighs[MAX_STATIC_TEXCOORDS];
	float weights[MAX_STATIC_TEXCOORDS];
};

class StaticMeshVertexBuffers
{
	StaticMeshVertexBuffer staticMeshVertexBuffer;
	PositionVertexBuffer positionVertexBuffer;
	ColorVertexBuffer colorVertexBuffer;
};


class AdditionalStaticMeshIndexBuffers
{
	RawStaticIndexBuffer reversedIndexBuffer;
	RawStaticIndexBuffer reversedDepthOnlyIndexBuffer;
	RawStaticIndexBuffer wriframeIndexBuffer;
};

class StaticMeshSectionArray :public std::vector<StaticMeshSection>
{
	using Super = std::vector<StaticMeshSection>;
public: 
	using Super::Super;
};


struct StaticMeshLODResources :public RefCountBase
{
public:
	StaticMeshLODResources();
	virtual ~StaticMeshLODResources();
	StaticMeshSectionArray sections;
	class DistanceFieldVolumeData* distanceFieldData = nullptr;
	class CardRepresentationData* cardRepresentationData;
	float mexDeviation;
	uint32 hasDepthOnlyIndices : 1;
	uint32 hasReversedIndices : 1;
	uint32 hasReversedDepthOnlyIndices : 1;
	uint32 hasColorVertexData : 1;
	uint32 hasWireframeIndices : 1;
	uint32 hasRayTracingGeometry : 1;
	uint32 buffersInlined : 1;
	uint32 isOptionalLOD : 1;
	uint32 depthOnlyNumTriangles;
	uint32 buffersSize;
	uint32 staticMeshIndexMemory;
	std::string derivedDattaKey;
	Array<int32>wedgeMap;
	StaticMeshVertexBuffers vertexBuffers;
	RawStaticIndexBuffer indexBuffer;
	RawStaticIndexBuffer DepthOnlyIndexBuffer;
	AdditionalStaticMeshIndexBuffers* additionalIndexBuffers = nullptr;

private:
	struct StaticMeshBuffersSize
	{
		uint32 serializedBuffersSize = 0;
		uint32 depthOnlyIBsSize = 0;
		uint32 reversedIBsSize = 0;
		void Clear()
		{
			serializedBuffersSize = 0;
			depthOnlyIBsSize = 0;
			reversedIBsSize = 0;
		}

		uint32 CalcBuffersSize()const;
	};
};


struct StaticMeshVertexFactories
{

};

using StaticMeshLODResourcesArray = Array<StaticMeshLODResources>;
using StaticMeshVertexFactoriesArray = Array<StaticMeshVertexFactories>;

class StaticMeshRenderData
{
public:
	StaticMeshRenderData();
	virtual ~StaticMeshRenderData();
    StaticMeshLODResourcesArray LODResources;
	StaticMeshVertexFactoriesArray LODVertexFactories;
	float screenSize[MAX_STATIC_MESH_LODS];
	BoxSphereBounds bounds;
	bool LODsShareStaticLighting;
	bool readyForStreaming;
	uint8 numInlinedLOGDs;
	uint8 currentFirestLOGIdx;
	uint8 LODBiasModifier;
	std::string derivedDataKey;
	Array<int32>materialIndexToImportIndex;
	Array<MeshUVChannelInfo>UVChannelDataPerMaterial;
	std::unique_ptr<StaticMeshRenderData>nextCacheRenderData;
	uint64 estimatedNaniteToTalCompressedSize = 0;
	uint64 estimatedNaniteStreamCompressedSize = 0;
};
