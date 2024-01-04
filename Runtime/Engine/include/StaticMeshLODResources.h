#pragma once
#include <memory>
#include <vector>
#include <string>
#include <map>
#include "StaticMeshVertexBuffer.h"
#define MAX_STATIC_TEXCOORDS 8
 struct StaticMeshSection
{
	int materialIndex;
	int firstIndex;
	int numTriangles;
	int minVertexIndex;
	int maxVertexIndex;
	bool enableCollision;
	bool castShadow;
	bool visibelInRayTraccing;
	bool affectDistanceFieldLighting;
	bool forceOpaque;
	float UVDensities[MAX_STATIC_TEXCOORDS];
	float widgets[MAX_STATIC_TEXCOORDS];
	StaticMeshSection() :
		materialIndex{ 0 },
		firstIndex{ 0 },
		numTriangles{ 0 },
		minVertexIndex{ 0 },
		maxVertexIndex{ 0 },
		enableCollision{ false },
		castShadow{ true },
		visibelInRayTraccing{ true },
		affectDistanceFieldLighting{ true },
		forceOpaque{ false }
	{
		memset(UVDensities, 0, sizeof(UVDensities));
		memset(widgets, 0, sizeof(widgets));
	}
};

 struct StaticMeshVertexBuffers
 {
	 StaticMeshVertexBuffer staticMeshVertexBuffer;
	 PositionVertexBuffer positionVertexBuffer;
	 ColorVertexBuffer colorVertexBuffer;
	 void InitModelBuffers(std::vector<class ModelVertex>& vertices);
	 void InitModelVF();
	 
 };
 using StaticMeshSectionArray = std::vector<StaticMeshSection>;
struct StaticMeshLODResources
{
	StaticMeshSectionArray sections;
	class DistanceFieldVolumeData*distanceFieldData=nullptr;
	class CardRepresentationData* cardRepresentationData;
	float MaxDeviation;
	int hasDepthOnlyIndices:1;
	int hasReversedInices:1;
	int hasReversedDepthOnlyIndeices;
	int hasColorVertexData : 1;
	int hasWireframeIndices : 1;
	int hasRayTracingGeometry : 1;
	int bufferInlined : 1;
	int isOptionalLOD : 1;
	int depthOnlyNumTriangles;
	int bufferSize;
	int staticMeshIndexMemory;
	std::string DeriveDataKey;
	std::vector<int>wedgeMap;
	StaticMeshVertexBuffers vertexBuffers;
	RawStaticIndexBuffer indexBuffer;
	RawStaticIndexBuffer depthOnlyIndexBuffer;
	AdditionalStaticMeshIndexBuffers* additionalIndexBuffers = nullptr;
	RayTracingGeomery rayTacingGeometry;

	struct StaticMeshBuffersSize
	{
		int serializedBuffersSize = 0;
		int DepthOnlyIBSize = 0;
		int reversedIBsSize = 0;
		void Clear()
		{
			serializedBuffersSize = 0;
			DepthOnlyIBSize = 0;
			reversedIBsSize = 0;
		}
		int CalcBuffersSize()const;
	};
};

